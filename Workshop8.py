from urllib import request
from lxml import html
import json

def parsePage(url, outputFile):
    try:
        open(outputFile, 'r').readlines()
    except:
        print("ERROR: No such file")
        return
    try:
        pageHTML = request.urlopen(url).read()
        parsedPage = html.fromstring(pageHTML)
        myResult = dict()
        for divElem in parsedPage.xpath("//a"):
            temporaryValue = divElem.get("href")
            if temporaryValue and temporaryValue[:8] == "https://":
                myResult[temporaryValue[8:]] = temporaryValue
        json.dump(myResult, open(outputFile, "w"))
    except NameError:
        print("Incorrect URL")
        return

url = input()
outputFile = input()
parsePage(url, outputFile)