import sys
import os
import hashlib

def compare(similar):
	hashes=[]
	
	#checking hash values of first 20 characters of each file
	#if the first 20 lines are not same then the files are definitely not duplicates
	for file in similar:
		fo=open(file, 'rb')
		h = hashlib.sha1()
		line=fo.read(20)
		h.update(line)
		hashes.append(h.digest())
		fo.close()
	
	#removing files that cannot be duplicates from the list of similar files
	flag=0
	for i in range(0, len(hashes)):
		if flag==1:
			i-=1
		if(hashes.count(hashes[i])==1):
			similar.pop(i)
			hashes.pop(i)
			flag=1
	hashes[:]=[]
	
	#checking hash values of the entire files that can be duplicates
	for file in similar:
		h = hashlib.sha1()
		fo=open(file, 'rb')
		line = 0
       		while line != b'':
           		line=fo.read(1024)
           		h.update(line)
		hashes.append(h.digest())
	
	#generating final list of duplicate files
	flag=0
	for i in range(0, len(hashes)):
		if flag==1:
			i-=1
		if(hashes.count(hashes[i])==1):
			similar.pop(i)
			hashes.pop(i)
			flag=1
	return similar
#----------------------------------------------------------------	
a=dict()
duplicates=dict()

if (sys.argv[1:]):
	arg=sys.argv[1]
else:
	arg="/home"

#traversing the filesystem tree
for root, dirs, files in os.walk(arg, topdown=True):
    for name in files:
        name= root+"/"+name
	
	similar=[]
	statinfo = os.stat(name)
        size=statinfo.st_size
	a.setdefault(size, [])
	a[size].append(name)	#grouping files according to their sizes
	similar=a.get(size)	#files having same size have the posibility of being duplicates
	
	if(len(similar)>1):
		dup=[]
		dup=compare(similar)	#obtaining list of duplicate files from list of same sized files
		for item in dup:
			duplicates.setdefault(size, [])
			if( item not in duplicates[size]):
				duplicates[size].append(item)	#grouping duplicates by size
print 
print
print "sets of duplicates are:"
for key in duplicates.keys():
	print "-------------------------------------"
	print
	i=0
	for item in duplicates[key]:
		print i, "" , item
		i=i+1
	print
	ch=raw_input("delete item??(y) ")
	if(ch=='y'):
		os.remove(duplicates[key][input("enter file no ")])
	print	

#=---------------------output------------------
#[lenovo@localhost hdd]$ python duplicate.py /home/lenovo/l3cube
#
#
#sets of duplicates are:
#-------------------------------------
#
#0  /home/lenovo/l3cube/hdd/hdd.txt
#1  /home/lenovo/l3cube/hdd/sample/hdd.txt
#
#delete item??(y)y
#enter file no 1
#
#-------------------------------------
#
#0  /home/lenovo/l3cube/dlies.txt
#1  /home/lenovo/l3cube/TestVectors/dlies.txt
#
#delete item??(y)g
#
#-------------------------------------
#
#0  /home/lenovo/l3cube/pcap/A look at the pcap file format | Hani's blog_files/photo_004.jpg
#1  /home/lenovo/l3cube/pcap/A look at the pcap file format | Hani's blog_files/photo_003.jpg
#
#delete item??(y)n
#
#-------------------------------------
#
#0  /home/lenovo/l3cube/dsa.txt
#1  /home/lenovo/l3cube/TestVectors/dsa.txt
#
#delete item??(y)n
#
#-------------------------------------
#
#0  /home/lenovo/l3cube/hdd/sample/test.py
#1  /home/lenovo/l3cube/hdd/sample/Untitled Folder/test (copy).py
#
#delete item??(y)y
#enter file no 1
#
#-------------------------------------
#
#0  /home/lenovo/l3cube/weblog.txt
#1  /home/lenovo/l3cube/http/weblog.txt
#
#delete item??(y)n
#
#[lenovo@localhost hdd]$ 
