from matplotlib import image, numpy, pyplot

class Image:
    
    def __init__(self, data):
        
        self.mat = matrix(data)
    
    def __repr__(self):
        
        self.show()
        return "%s x %s Image" % self.size()
                
    def size(self):
        
        return (self.mat.nrows(), self.mat.ncols())
    
    def show(self):
    
        #image.imsave(".temp.png", self.data)
        #display(pyImage(".temp.png"))
        pyplot.imshow(self.mat, cmap="gray")
   
def RandomImage(m, n):
    
    return Image(numpy.random.randint(256, size=(m,n,3)) )
    
def LoadImage(filename):
    
    return Image(image.imread(filename))
