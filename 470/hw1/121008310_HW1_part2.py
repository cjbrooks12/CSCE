import sys
import re
import operator
import glob
import os
import math
import sets

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
    self.magnitude = 0
    self.cosine = 0


corpus = Corpus()

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

def query(q):
  global corpus
  rankedDocs = []
  raw_query_words = re.split('\W+', q)
  queryWords = []
  
  for word in raw_query_words:
    if len(word) >= 3:
      key = word.lower()
      queryWords.append(key)
      
  queryWords = sets.Set(queryWords)
  
  # Since we consider the value of each word in the query to be 1, we can take the 
  # length simply as the square root of its length
  queryMagnitude = len(queryWords)**0.5
  
  # Since we consider the value of each worf in the query to be 1, we can get the 
  # dot product of the query and document vectors simply as the sum of TF-IDFs 
  # of each word in the query
  
  for doc in corpus.documents:
    dotProduct = 0
    for word in queryWords:
      if word in doc.tf_idf:
        dotProduct += doc.tf_idf[word]

    doc.cosine = dotProduct / (queryMagnitude*doc.magnitude)

  corpus.documents.sort(key=lambda doc: doc.cosine, reverse=True)
  
  for (idx, doc) in enumerate(corpus.documents[:5]):
    print str(idx) + ": " + doc.name + " (" + str(doc.cosine) + ")"
    
  sys.stdout.flush()
   
  return 

def read_input(filename):
  f = open(filename, 'r')
  raw_query = ""
  
  for line in f:
    raw_query += line + " "
    
    query(raw_query)

def main():
  if len(sys.argv) != 3:
    print 'usage: ./121008310_HW1_part2.py <folder> <query file>'
    sys.exit(1)
  folder = sys.argv[1]
  filenames = [fn for fn in os.listdir(folder) if fn.endswith('.txt')]
  filenames.sort()
  build_index(folder, filenames)
  read_input(sys.argv[2])

if __name__ == '__main__':
  main()