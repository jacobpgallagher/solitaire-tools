#!/usr/bin/env python

import subprocess
import sys,os
import random
import time
import math
import tarfile
import tempfile

#stdout is key
#stderr is stream

DECKSIZE=9
HASHSHIFTS=min(2,DECKSIZE)
#HASHSHIFTS=DECKSIZE

def recursemkdir(folder, num, morelevels):
    if morelevels > 0:
        for i in range(num):
            os.mkdir(os.path.join(folder, str(i)))
            recursemkdir(os.path.join(folder, str(i)), num, morelevels-1)

class hash:
    def __init__(self):
        self.hashTable=[]
        size=0
        for i in range(DECKSIZE-1,(DECKSIZE -1) - HASHSHIFTS, -1):
            shift=int(math.ceil(math.log(DECKSIZE,2)) * ((HASHSHIFTS - ((DECKSIZE -1) -i)) - 1))
            size = size + (i << shift)
        print "size: %i" % size
        i = 0;
        while i < size + 1:
            self.hashTable.append(False)
            i += 1


                
    def hash(self, toHash, write=True):
        key = 0
        for i in range(HASHSHIFTS):
            toadd=(ord(toHash[i])-1) << int(math.ceil(math.log(DECKSIZE,2)) * i)
            key += toadd

        if self.hashTable[key]:
            for i in range(0,len(self.hashTable[key]),DECKSIZE):
                if self.hashTable[key][i:i+DECKSIZE]==toHash:
                    return True
            if write:
                self.hashTable[key]+=toHash
            return False
        else:
            if write:
                self.hashTable[key]=toHash
            return False


if __name__=="__main__":

    folder=sys.argv[1]

    totallyDone=False
    
    allkeyFiles=[]
    key = range(DECKSIZE)
    keyhash = hash()
    loophash = hash()

    tar=tarfile.open(os.path.join(folder, "Data.tar"),"w:")


    

    while not totallyDone:

        inLoop=False

        keyforProc = ""
        keyforFilename=[]
        for i in key:
            keyforProc = keyforProc + chr(i + 48)
            keyforFilename.append(str(i))

        keyforFilename="-".join(keyforFilename)


        fkeyout=tempfile.TemporaryFile()
        fstreamout=tempfile.TemporaryFile()

        proc=subprocess.Popen(["./dumper", keyforProc], stdout=subprocess.PIPE, stderr=subprocess.PIPE, close_fds=True)


        tmp=""
        hashed=False
        while not hashed:
            tmp = proc.stdout.read(DECKSIZE)
            if len(tmp)!=DECKSIZE:
                print keyforProc
                print proc.stderr.read()
                raise Exception("tmp = %i" % len(tmp))
            hashed=keyhash.hash(tmp) or loophash.hash(tmp, False)
            #fkeyout.write(tmp)
            proc.stderr.read(1)
            #fstreamout.write(proc.stderr.read(1))
#        fstreamout.close()
#        fkeyout.close()

        if not loophash.hash(tmp, False):

            keyString=""
            for i in range(len(tmp)):
                keyString = keyString + str(ord(tmp[i])) + "-"
            keyString=keyString[:len(keyString)-1]

            keyTar=tarfile.TarInfo(keyString + ".key")
            streamTar=tarfile.TarInfo(keyString + ".stream")


            hashed=False
            while not hashed:
                tmp = proc.stdout.read(DECKSIZE)
                if len(tmp)!=DECKSIZE:
                    print keyforProc
                    print proc.stderr.read()
                    raise Exception("tmp = %i" % len(tmp))
                hashed=loophash.hash(tmp)
                fkeyout.write(tmp)
                fstreamout.write(proc.stderr.read(1))


            keyTar.size=fkeyout.tell()
            streamTar.size=fstreamout.tell()
            fkeyout.seek(0)
            fstreamout.seek(0)
            tar.addfile(keyTar, fkeyout)
            tar.addfile(streamTar,fstreamout)


        while proc.poll()==None:
            os.kill(proc.pid, 9)

        fstreamout.close()

        usedKey=True

        try:
            while usedKey:
                random.shuffle(key)

                keystring=""
                for i in key:
                    keystring = keystring + chr(i + 1)

                usedKey=keyhash.hash(keystring, False) or loophash.hash(keystring,False)
                if usedKey:
                    print "Bad:"
                else:
                    print "Good:"
                for num in key:
                    print num,
                print ""
        except:
            tar.close()
            sys.exit(0)
