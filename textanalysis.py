import sys
from textblob import TextBlob
import json

text = sys.argv[1]
uuid = sys.argv[2]

analysis = TextBlob(sys.argv[1])

file = open('analysis_' + uuid + '.json', "w")
file.write(json.dumps({
    "polarity": analysis.polarity,
    "subjectivity": analysis.subjectivity
}))