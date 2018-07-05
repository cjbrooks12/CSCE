import sys
import re
import operator
import glob
import os
import math

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


corpus = Corpus()

def build_index(filedir, filenames):
  global corpus

  # Load files into tf vectors
  count = 0
  for filename in filenames:
    f = open(filedir + "/" + filename, 'r')
    document = Document()
    document._id = count
    document.name = filename
    
    count += 1
    
    for line in f:
      words = re.split('[\s+]', line)
      for word in words:
        if len(word) == 6:
          key = word.lower()
          
          # add to tf of the document
          document_val = document.dictionary.get(key, 0)
          document.dictionary[key] = document_val + 1
          
          # if this is the first time this word occurs in the doc, add it to the df corpus
          if document_val == 0:
            corpus_val = corpus.dictionary.get(key, 0)
            corpus.dictionary[key] = corpus_val + 1
    
    corpus.documents.append(document)
    
    
  # Convert tf values into tf-idf values
  
  for word, df in corpus.dictionary.iteritems():
    for word in doc.dictionary:
      tf = 1 + math.log10(doc.dictionary[word])
      idf = math.log10(len(corpus.documents) / math.log10(corpus.dictionary[word]))
      doc.tf_idf[word] = tf + idf
      
    
  return

def query(q):
  global corpus
  # for doc in corpus.documents:
  print "results with query '" + q + "'"
  print "result 1"  
  print "result 2"  
  print "result 3"  
  print "result 4"  
  print "result 5"  
  return 

def input_loop():
  while True:
    input_query = raw_input("Enter query, or :q to quit: ")
    if input_query == ":q":
      break
    
    print "Search results: "
    query(input_query)
    

  

def main():
  if len(sys.argv) != 2:
    print 'usage: ./121008310_HW1_part2.py <folder>'
    sys.exit(1)
  folder = sys.argv[1]
  filenames = [fn for fn in os.listdir(folder) if fn.endswith('.txt')]
  build_index(folder, filenames)
  input_loop()

if __name__ == '__main__':
  main()