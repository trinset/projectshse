import argparse, sys
import pandas as pd


parser = argparse.ArgumentParser(description='console application')
parser.add_argument("--input_file", type=str, help="input : pandas file name")
parser.add_argument("--output_file", help="output : pandas file name", action='store_true')
parser.add_argument("--columns", type=str, help="list of columns to select from input csv file", nargs='*')
parser.add_argument("--query", type=str, help="query string to apply", nargs='*')
args = parser.parse_args()

if args.input_file:
    try:
        data = pd.read_csv(args.input_file)
        print(data)
        pass
    except Exception as e:
        print("ERROR")
        sys.exit(0)

if args.columns:
    try:
        listOfColumns = args.columns
        data = data[listOfColumns]
        pass
    except Exception as e:
        print("ERROR")
        sys.exit(0)

if args.query:
    try:
        b = args.query[0]
        data = data.query(b)
        pass
    except Exception as e:
        print("ERROR")
        sys.exit(0)

if args.output_file:
    try:
        print(data)
        pass
    except Exception as e:
        print("ERROR")
        sys.exit(0)