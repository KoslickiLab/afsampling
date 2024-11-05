"""
data looks like this:  
100000,96.65,10.669,790,23.253,518.5,330.142
1000000,1005.9,37.0876,1024.95,28.7758,1665.25,1052.13
10000000,10012.2,107.809,1250.1,34.3204,5241.95,3336.51
100000000,99946.6,286.641,1479.7,45.2328,16551.2,10576.4
"""


from matplotlib import pyplot as plt
import pandas as pd
import numpy as np

df = pd.DataFrame(columns=['size', 'fmh_size_avg', 'fmh_size_std', 'aff_size_avg', 'aff_size_std', 'alpha_afs_size_avg', 'alpha_afs_size_std'])
df.loc[0] = [10000,10.1,4.22966,561.3,14.9803,167.75,105.652]
df.loc[1] = [100000,96.65,10.669,790,23.253,518.5,330.142]
df.loc[2] = [1000000,1005.9,37.0876,1024.95,28.7758,1665.25,1052.13]
df.loc[3] = [10000000,10012.2,107.809,1250.1,34.3204,5241.95,3336.51]
df.loc[4] = [100000000,99946.6,286.641,1479.7,45.2328,16551.2,10576.4]


k = 100

plt.plot(np.log10(df['size']), np.log10(df['size']/1000), label='FMH Expected Size', alpha=0.5, marker='o')
plt.plot(np.log10(df['size']), np.log10( k*np.log(df['size']/k)+k ), label='AFF Expected Size', alpha=0.5, marker='o')


# plot fmh_avg against size, x axis in logarithmic
plt.plot(np.log10(df['size']), np.log10(df['aff_size_avg']), label='AFF Sketch Size', alpha=0.5, marker='o')
plt.plot(np.log10(df['size']), np.log10(df['fmh_size_avg']), label='FMH Sketch Size', alpha=0.5, marker='o')

plt.plot(np.log10(df['size']), np.log10(df['alpha_afs_size_avg']), label='aAS Sketch Size', alpha=0.5, marker='o')


plt.xlabel('log10 of Size')
plt.ylabel('log10 of Sketch Size')

plt.legend()

plt.savefig('plotSketchSizes.svg')
