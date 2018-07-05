import sys
import re
import operator
import glob
import os

def print_top_five(filenames):
  hist = {}

  for filename in filenames:
    f = open(filename, 'r')
    for line in f:
      words = re.split('[\s+]', line)
      for word in words:
        if len(word) == 6:
          key = word.lower()
          val = hist.get(key, 0)
          hist[key] = val + 1
        
  sorted_hist = sorted(hist.items(), key=operator.itemgetter(1), reverse=True)
  count = 0
  for key, value in sorted_hist[:5]:
    count += 1
    print str(count) + ': ' + key + ': ' + str(value)
    
  return

def main():
  if len(sys.argv) != 2:
    print 'usage: ./121008310_part3.py <folder>'
    sys.exit(1)
  folder = sys.argv[1]
  filenames = [fn for fn in os.listdir(folder) if fn.endswith('.txt')]
  print_top_five(filenames)

if __name__ == '__main__':
  main()