import sys
import re
import operator
import glob
import os
import math
import sets
import copy
from random import randint
from sets import Set

class Corpus:
  def __init__(self):
    self.dictionary = {}
    self.documents = []
  
class Document:
  def __init__(self):
    self.dictionary = {}
    self.tf_idf = {}
    self._id = 0
    self.name = ''

class Cluster:
  def __init__(self):
    self.centroid = {}
    self.documents = []
    self._id = 0;
    self.initialSeed = 0;

corpus = Corpus()
clusters = []
numClusters = 0;
iterations = 0;
iteration = 0;
lastIterationsPurity = 0;
thisIterationsPurity = 0;


# Create the index
#-------------------------------------------------------------------------------
def build_index(filedir, filenames):
  global corpus

  #create tf and df values for each document in the corpus
  count = 0
  for filename in filenames:
    f = open(filedir + "/" + filename, 'r')
    document = Document()
    document._id = count
    document.name = filename
    
    count += 1
    for line in f:
      words = re.split('\W+', line)
      for word in words:
        if len(word) >= 3:
          key = word.lower()
          
          # add to tf of the document
          document_val = document.dictionary.get(key, 0)
          document.dictionary[key] = document_val + 1
          
          # if this is the first time this word occurs in the doc, add it to the df corpus
          if document_val == 0:
            corpus_val = corpus.dictionary.get(key, 0)
            corpus.dictionary[key] = corpus_val + 1
    
    corpus.documents.append(document)
    
  # apply log transforms and calculate the magnitude of each document
  for doc in corpus.documents:
    totalLength = 0
    for word, count in doc.dictionary.iteritems():
      doc.tf_idf[word] = (math.log10(count) + 1) * math.log10(corpus.dictionary[word])
      totalLength += doc.tf_idf[word]**2
    doc.magnitude = totalLength**0.5
  return

# aux functions for calculating clusters
#-------------------------------------------------------------------------------

def initializeSeeds():
  del clusters[:];
  seeds = "\nrandom seeds: [";
  for i in range(numClusters):
    rand = randint(0, len(corpus.documents) - 1);
    seeds += str(rand) + ", ";
    newCluster = Cluster();
    newCluster.centroid = copy.deepcopy(corpus.documents[rand].tf_idf); 
    newCluster._id = i;
    newCluster.initialSeed = rand;
    clusters.append(newCluster);
  print seeds[:-2] + "]";

# calculate the euclidian distance from a document to a cluster's centroid
def euclidianDistance(doc, cluster):
  distance = 0;
  for word in corpus.dictionary:
    diff = (doc.tf_idf.get(word, 0) - cluster.centroid.get(word, 0))**2;
    distance += diff;
  distance = distance**0.5;
  return distance;
  
# calculate the angle between a document and a cluster's centroid
def cosine(doc, cluster):
  dotProduct = 0;
  docMagnitude = 0;
  clusterMagnitude = 0;
  for word in corpus.dictionary:
    dotProduct += doc.tf_idf.get(word, 0) * cluster.centroid.get(word, 0);
    docMagnitude += doc.tf_idf.get(word, 0)**2;
    clusterMagnitude += cluster.centroid.get(word, 0)**2;
    
  if docMagnitude == 0 or clusterMagnitude == 0:
    return 0;
  else:
    return (dotProduct / ((docMagnitude**0.5)*(clusterMagnitude**0.5)));
  
# assign each document to a cluster by finding the closest centroid
def assignClusters():
  for cluster in clusters:
    del cluster.documents[:];
          
  for doc in corpus.documents:
    closest = sys.maxint;
    clusterIndex = 0;
    for i in range(numClusters):
      if (iteration % 2) == 0:
        distance = euclidianDistance(doc, clusters[i]);
      else:
        distance = cosine(doc, clusters[i]);
      
      if distance < closest:
        closest = distance;
        clusterIndex = i;
    clusters[clusterIndex].documents.append(doc);
  return;

# calculate the new centroids of each cluster given its list of documents
def computeCentroids():
  for cluster in clusters:
    for word in corpus.dictionary:
      totalVal = 0;
      count = 0;
      for doc in cluster.documents:
        totalVal += doc.tf_idf.get(word, 0);
        count += 1;
      cluster.centroid[word] = totalVal / count if count > 0 else 0;
  
  return;
  
def evaluateClusters():
  
  global lastIterationsPurity;
  global thisIterationsPurity;
  
  clusterTypes = [];
  purity = 0;
  totals = {};
  for cluster in clusters:
    docTypes = {}
    for doc in cluster.documents:
      docType = doc.name[4:]
      
      # increment the count for the cluster
      docTypeCount = docTypes.get(docType, 0)
      docTypes[docType] = docTypeCount + 1
      
      # increment the global count so we can be sure we still have everything
      totalCount = totals.get(docType, 0)
      totals[docType] = totalCount + 1
      
    if len(docTypes.keys()) > 0: 
      greatestDocType = max(docTypes.iteritems(), key=operator.itemgetter(1))[0];
      clusterPurity = float(docTypes[greatestDocType]) / float(len(corpus.documents));
      purity += clusterPurity;
      if clusterPurity > ((1.0 / numClusters) / 2):
        clusterTypes.append(greatestDocType);

    print "[" + str(cluster._id) + "]: numClusterTypes=[" + str(len(Set(clusterTypes))) + "], clusterPurity=[" + str(clusterPurity) + "], totalPurity=[" + str(purity) + "]";

  lastIterationsPurity = thisIterationsPurity;
  thisIterationsPurity = purity;

  return len(Set(clusterTypes)) == numClusters;

    
# create and print a histogram of the topics for each document in a cluster
def printResults():
  print "\nResults:\n##################################################"
  totals = {};
  for cluster in clusters:
    docTypes = {}
    for doc in cluster.documents:
      docType = doc.name[4:]
      
      # increment the count for the cluster
      docTypeCount = docTypes.get(docType, 0)
      docTypes[docType] = docTypeCount + 1
      
      # increment the global count so we can be sure we still have everything
      totalCount = totals.get(docType, 0)
      totals[docType] = totalCount + 1
      
    print "[" + str(cluster._id) + "]: initialSeed=" + str(cluster.initialSeed) + ": " + str(sorted(((v,k) for k,v in docTypes.iteritems()), reverse=True));
  print "##################################################"
  print "totals: " + str(totals);
  
# Main function
#-------------------------------------------------------------------------------
def main():
  
  global numClusters;
  global iterations;
  global iteration;
  global lastIterationsPurity;
  global thisIterationsPurity;

  if len(sys.argv) != 3:
    print 'usage: ./121008310_HW1_part2.py <folder> <query file>'
    sys.exit(1)
  folder = sys.argv[1];
  
  numClusters = 5;
  iterations = 20;
  maxIterations = 200;
  
  filenames = [fn for fn in os.listdir(folder)]
  filenames.sort();
  build_index(folder, filenames)
  
  initializeSeeds();
  seedNumber = 1;

  while True:
    iteration = iteration + 1;
    print "\niteration [" + str(iteration) + "] seedNumber=[" + str(seedNumber) + "]";
    assignClusters();
    computeCentroids();
    
    if(evaluateClusters()):
      printResults();
      break;
    elif lastIterationsPurity == thisIterationsPurity:
      initializeSeeds();
      seedNumber += 1;
    elif iteration == maxIterations:
      printResults();
      break;

if __name__ == '__main__':
  main()
  
