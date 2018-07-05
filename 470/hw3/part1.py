import sys
import requests
import json
import os
import re
from sys import argv

API_KEY = 'cjbrooks12:ziraAVnlwm8xSqRXrfoBwsc8jHI5iac6dZDGTu8nprQ';

def createUrl(query, start, num):
  words = query.split();
  url = 'https://' + API_KEY + '@api.datamarket.azure.com/Bing/Search/v1/Web?Query=%27';
  
  for word in words:
    url += word + '%20';
    
  url += '%27&$format=json&$skip=' + str(start) + '&$top=' + str(num);
  
  return url;

def main():
  if not os.path.exists('./data'):
    os.makedirs('./data')
  
  docNumber = 0;
  for query in ['texas aggies', 'texas longhorns', 'houston texans', 'houston rockets', 'dallas cowboys']:
    for i in range(5):
      url = createUrl(query, i*10, 10);
      r = requests.get(url).json()
      for i in r['d']['results']:
        docNumber += 1;
        
        filename = str(docNumber).zfill(3) + '_' + re.sub(r'\s', '_', query);
        content = str(i['Title'].encode('ascii', 'ignore')) + '\n' + str(i['Description'].encode('ascii', 'ignore'));
        
        f1=open('./data/' + filename, 'w+')
        f1.write(content)
        
if __name__ == '__main__':
  main()
  