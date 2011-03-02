#!/usr/bin/env python

import subprocess
import sys,os
import random
import time
import math

#stdout is key
#stderr is stream

DECKSIZE=54
HASHSHIFTS=min(4,DECKSIZE)

def recursemkdir(folder, num, morelevels):
    if morelevels > 0:
        for i in range(num):
            os.mkdir(os.path.join(folder, str(i)))
            recursemkdir(os.path.join(folder, str(i)), num, morelevels-1)

class hash:
    def __init__(self, folder):
        self.folder=folder
        self.hashTable=[]
        size=0
        for i in range(DECKSIZE-1,(DECKSIZE -1) - HASHSHIFTS, -1):
            shift=int(math.ceil(math.log(DECKSIZE,2)) * ((HASHSHIFTS - ((DECKSIZE -1) -i)) - 1))
            #print "i: %i, shift: %i" % (i, shift)
            size = size + (i << shift)
        print "size: %i" % size
        i = 0;
        while i < size + 1:
            self.hashTable.append(False)
            i += 1


        recursemkdir(self.folder, DECKSIZE, HASHSHIFTS-1)
                
    def hash(self, toHash):
        key = 0
        directory = self.folder
        for i in range(HASHSHIFTS):
            toadd=(ord(toHash[i])-1) << int(math.ceil(math.log(DECKSIZE,2)) * i)
            directory = os.path.join(directory,str(ord(toHash[i])-1))
#            print "Adding %i (%i)" % (toadd, i)
            key += toadd

  #      print ord(toHash[0])
   #     print ord(toHash[1])
    #    print key
        if self.hashTable[key]:
            reader=open(directory + ".hash")
            tmp = reader.read(len(toHash))
            while len(tmp) == len(toHash):
                if toHash == tmp:
                    return True
                tmp=reader.read(len(toHash))
            reader.close()
        else:
            self.hashTable[key]=True
        writer=open(directory + ".hash", "a")
        writer.write(toHash)
        writer.close()
        return False

if __name__=="__main__":

    folder=sys.argv[1]

    totallyDone=False
    
    allkeyFiles=[]
    key = range(DECKSIZE)
    try:
        os.mkdir(os.path.join(folder, "hashtables"))
    except:
        pass
    hasher = hash(os.path.join(folder, "hashtables"))


    while not totallyDone:

        keyforProc = ""
        keyforFilename=[]
        for i in key:
            keyforProc = keyforProc + chr(i + 32)
            keyforFilename.append(str(i))

        keyforFilename="-".join(keyforFilename)

        fkeyout=open(os.path.join(folder,keyforFilename+".key"),"w")
        fstreamout=open(os.path.join(folder,keyforFilename+".stream"),"w")

        proc=subprocess.Popen(["./dumper", keyforProc], stdout=subprocess.PIPE, stderr=subprocess.PIPE, close_fds=True)

        hashed=False
        while not hashed:
            tmp = proc.stdout.read(DECKSIZE)
            hashed=hasher.hash(tmp)
            fkeyout.write(tmp)
            fstreamout.write(proc.stderr.read(1))
        fstreamout.close()
        fkeyout.close()


        while proc.poll()==None:
            time.sleep(1)
            os.kill(proc.pid, 9)

        fstreamout.close()

        usedKey=True

        while usedKey:
            random.shuffle(key)

            keystring=""
            for i in key:
                keystring = keystring + chr(i + 1)

            usedKey=hasher.hash(keystring)
            if usedKey:
                print "Bad:"
            else:
                print "Good:"
            for num in key:
                print num,
            print ""

        
