import argparse, os, time


def decimalRound(rounded): #round to the closest non-zero number after decimal point
    rounded = str(rounded)
    k = 0
    s = 0
    while rounded[k] != "." and k != (len(rounded) - 1):
        k += 1
    k += 1
    s += 1
    while rounded[k] == "0" and k != (len(rounded) - 1):
        k += 1
        s += 1
    rounded = round(float(rounded), s)
    return str(rounded)


parser = argparse.ArgumentParser(description='console application',
                                 formatter_class=argparse.RawTextHelpFormatter)
parser.add_argument("-size", "-s", type=str, help='print size of the file in MB')
parser.add_argument("-rename", type=str, nargs=2, help="change file name to B \n"
                                                       "input: chosen file and a new name")
parser.add_argument("-mtime", type=str, nargs=2, help="print modification time \ninput: file and time format:\n"
                                                      "date   date only\n"
                                                      "time   time only\n"
                                                      "dnt    date and time")
args = parser.parse_args()
if args.size:
    print(decimalRound(os.stat(args.size).st_size / (2 ** 20)), "MB")
if args.rename:
    os.rename(args.rename[0], args.rename[1])
if args.mtime:
    my_time = time.ctime(os.stat(args.mtime[0]).st_mtime)
    k = 0
    while my_time[k] != ":":
        k += 1
    mtime_date = my_time[:k-3] + my_time[k+6:]
    mtime_time = my_time[k-2:k+6]
    if args.mtime[1] == "date":
        print(mtime_date)
    elif args.mtime[1] == "time":
        print(mtime_time)
    elif args.mtime[1] == "dnt":
        print(my_time)
    else:
        print("Error. That's the date and time though!", my_time)