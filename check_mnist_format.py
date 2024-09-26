from numpy import array
#   checks if the files are indeed in the correct format of the mnist database https://yann.lecun.com/exdb/mnist/
#	magic number
#	size in dimension 0
#	size in dimension 1
#	size in dimension 2
#	.....
#	size in dimension N
#	data
#	
#	The magic number is an integer (MSB first). The first 2 bytes are always 0.
#	
#	The third byte codes the type of the data:
#	0x08: unsigned byte
#	0x09: signed byte
#	0x0B: short (2 bytes)
#	0x0C: int (4 bytes)
#	0x0D: float (4 bytes)
#	0x0E: double (8 bytes)
#	The 4-th byte codes the number of dimensions of the vector/matrix: 1 for vectors, 2 for matrices....
#	2051 or 0x803 means a tensor of unsigned bytes
#	2049 or 0x801 means a vector of unsigned bytes

#	TRAINING SET LABEL FILE (train-labels-idx1-ubyte):
#	[offset] [type]          [value]          [description]
#	0000     32 bit integer  0x00000801(2049) magic number (MSB first)
#	0004     32 bit integer  60000            number of items
#	0008     unsigned byte   ??               label
#	0009     unsigned byte   ??               label
#	........
#	xxxx     unsigned byte   ??               label
#	The labels values are 0 to 9.
#	
#	TRAINING SET IMAGE FILE (train-images-idx3-ubyte):
#	[offset] [type]          [value]          [description]
#	0000     32 bit integer  0x00000803(2051) magic number
#	0004     32 bit integer  60000            number of images
#	0008     32 bit integer  28               number of rows
#	0012     32 bit integer  28               number of columns
#	0016     unsigned byte   ??               pixel
#	0017     unsigned byte   ??               pixel
#	........
#	xxxx     unsigned byte   ??               pixel
#	Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).
#	
#	TEST SET LABEL FILE (t10k-labels-idx1-ubyte):
#	[offset] [type]          [value]          [description]
#	0000     32 bit integer  0x00000801(2049) magic number (MSB first)
#	0004     32 bit integer  10000            number of items
#	0008     unsigned byte   ??               label
#	0009     unsigned byte   ??               label
#	........
#	xxxx     unsigned byte   ??               label
#	The labels values are 0 to 9.
#	
#	TEST SET IMAGE FILE (t10k-images-idx3-ubyte):
#	[offset] [type]          [value]          [description]
#	0000     32 bit integer  0x00000803(2051) magic number
#	0004     32 bit integer  10000            number of images
#	0008     32 bit integer  28               number of rows
#	0012     32 bit integer  28               number of columns
#	0016     unsigned byte   ??               pixel
#	0017     unsigned byte   ??               pixel
#	........
#	xxxx     unsigned byte   ??               pixel

def join_hex(x):
    s=""
    for i in range(4):
        y=hex(x[i]).replace('0x', '')
        y='0'*(2-len(y))+y
        s+=y
    return int(s, 16)
with open('train_imgs', 'rb') as f: train= f.read()
train=list(map(int, train))
print(join_hex(train[0:4])) # 2051
print(join_hex(train[4:8])) # 1000 
print(join_hex(train[8:12])) # 28
print(join_hex(train[12:16])) # 28
train = train[16:]
train=array(train[0:28*28]).reshape(28, 28)
with open('test_imgs', 'rb') as f: test= f.read()
test=list(map(int, test))
print(join_hex(test[0:4])) # 2051
print(join_hex(test[4:8])) # 1000 
print(join_hex(test[8:12])) # 28
print(join_hex(test[12:16])) # 28
test = test[16:]
test=array(test[0:28*28]).reshape(28, 28)
with open('train_labels', 'rb') as f: train_labels= f.read()
train_labels = list(map(int, train_labels))
print(join_hex(train_labels[0:4])) # 2049
print(join_hex(train_labels[4:8])) # 1000 
with open('test_labels', 'rb') as f: test_labels= f.read()
test_labels = list(map(int, test_labels))
print(join_hex(test_labels[0:4])) # 2049
print(join_hex(test_labels[4:8])) # 1000
test_labels = test_labels[8:]
print(test_labels[0:10])
