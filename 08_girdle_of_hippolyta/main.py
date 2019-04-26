#! /usr/bin/env python3

import yagmail
import os
import sys

def main():
    if len(sys.argv) != 3:
        print("usage: ./main.py person@example.com subject")
        sys.exit(1)
    try:
        try:
            FROM = os.environ['EMAIL_FROM']
            FROM_PASS = os.environ['EMAIL_FROM_PASS']
            TO = sys.argv[1]
            SUBJECT = sys.argv[2]
        except:
            print("Make sure EMAIL_FROM and EMAIL_FROM_PASS environment variables are set")
            sys.exit(1)
        sys.stdout.write('Email:\n')
        sys.stdout.write('> ')
        sys.stdout.flush()
        MSG = ""
        for line in sys.stdin:
            MSG += line
            sys.stdout.write('> ')
            sys.stdout.flush()
        yagmail.SMTP(FROM, FROM_PASS).send(TO, SUBJECT, MSG)
    except Exception as ex:
        print("Error sending message")
        print(ex)
        sys.exit(1)

if __name__ == "__main__":
    main()
