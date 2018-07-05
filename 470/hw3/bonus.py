import sys
import re
import operator
import glob
import os
import math
import sets
import copy
from random import randint

class Dialog:
  def __init__(self):
    self.season = 0;
    self.episode = 0;
    self.character = "";
    self.line = "";
    
class Character:
  def __init__(self, name):
    self.name = name;
    self.lines = [];
  
validCharacters = {
  'Stan'.lower(): Character('Stan'),
  'Cartman'.lower(): Character('Cartman'),
  'Kyle'.lower(): Character('Kyle'),
  'Kenny'.lower(): Character('Kenny'),
  'Mr. Garrison'.lower(): Character('Mr. Garrison'),
  'Chef'.lower(): Character('Chef')
};

# Create the index
#-------------------------------------------------------------------------------
def readTrainingFiles(filedir, filenames):
  totalLines = 0;
  validLines = 0;
  for filename in filenames:
    f = open(filedir + "/" + filename, 'r')
    
    for line in f:
      totalLines += 1;
      cols = re.split(',', line)
      if len(cols) != 4:
        continue;
      
      line = Dialog();
      try:
        line.season = int(cols[0].lower());
        line.episode = int(cols[1].lower());
        line.character = cols[2].lower();
        line.line = cols[3].lower();
      except ValueError:
        continue;
      
      if isValidCharacter(line.character):
        validCharacters[line.character].lines.append(line);
        validLines += 1;
  print "valid lines: " + str(validLines) + "/" + str(totalLines);
  return

def isValidCharacter(characterName):
  return True if characterName in validCharacters else False;
    
  
# Main function
#-------------------------------------------------------------------------------
def main():
  if len(sys.argv) != 2:
    print 'usage: ./bonus.py <folder>'
    sys.exit(1)
  
  global numClusters;

  folder = sys.argv[1]
  filenames = [fn for fn in os.listdir(folder)]
  filenames.sort();
  readTrainingFiles(folder, filenames)
  
  for key, character in validCharacters.iteritems():
    print character.name + ": " + str(len(character.lines)) + " lines"
  

if __name__ == '__main__':
  main()
  
