import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as tri
a=np.genfromtxt("../Raffinamento/Dataset/Test2/outputCell0Ds.csv");
b=np.genfromtxt("../Raffinamento/Dataset/Test2/outputCell2Ds.csv",skip_header=1);
x=a[1:,1]
y=a[1:,2]
triangles=b[:,1:4]
triang=tri.Triangulation(x,y,triangles)
plt.triplot(triang)
plt.savefig("../Raffinamento/Dataset/Test2/NewMesh.png")
plt.close()