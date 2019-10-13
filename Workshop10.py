from urllib import request
import urllib
from lxml import html
import json

def parsePage(url):
    try:
        pageHTML = request.urlopen(url).read()
        parsedPage = html.fromstring(pageHTML)
        myResult = dict()
        for divElem in parsedPage.xpath("//a"):
            temporaryValue = divElem.get("href")
            if temporaryValue and temporaryValue[:8] == "https://":
                myResult[temporaryValue[8:]] = temporaryValue
        return myResult
    except NameError:
        print("Incorrect URL")
        pass
    except urllib.error.HTTPError:
        pass
    except urllib.error.URLError:
        pass
    except UnicodeEncodeError:
        print(url)
        pass

def recParsePage(myResult, n, visPage):
    if n > 1000:
        return
    if myResult:
        for k in myResult:
            if k not in visPage:
                recParsePage(parsePage(myResult[k]), n+1, visPage + [k])
                outputJson[k] = myResult[k]
    return


url = input()
outputFile = input()
try:
    open(outputFile, 'r').readlines()
except:
    print("ERROR: No such file")
n = 0
myResult = parsePage(url)
visPage = []
outputJson = dict()
recParsePage(myResult, n, visPage)
json.dump(outputJson, open(outputFile, "w"))