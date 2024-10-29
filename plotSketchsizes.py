"""
data looks like this:  
10000,10.2,2.6,573,8.82043
100000,96.5,7.32462,790.3,31.8624
1000000,1004.2,26.5548,1021,30.4335
10000000,9968.3,73.369,1247,42.1829
100000000,97035.5,302.213,1486.3,24.0626

columns are: size, fmh_size_avg, fmh_size_std, aff_size_avg, aff_size_std
"""


from matplotlib import pyplot as plt
import pandas as pd
import numpy as np

df = pd.DataFrame(columns=['size', 'fmh_size_avg', 'fmh_size_std', 'aff_size_avg', 'aff_size_std'])
df.loc[0] = [10000,10.2,2.6,573,8.82043]
df.loc[1] = [100000,96.5,7.32462,790.3,31.8624]
df.loc[2] = [1000000,1004.2,26.5548,1021,30.4335]
df.loc[3] = [10000000,9968.3,73.369,1247,42.1829]
df.loc[4] = [100000000,97035.5,302.213,1486.3,24.0626]

# plot fmh_avg against size, x axis in logarithmic
plt.plot(np.log10(df['size']), np.log10(df['fmh_size_avg']), label='FMH Sketch Size', alpha=0.5, marker='o')    
plt.plot(np.log10(df['size']), np.log10(df['aff_size_avg']), label='AFF Sketch Size', alpha=0.5, marker='o')

plt.xlabel('log10 of Size')
plt.ylabel('log10 of Sketch Size')

plt.legend()

plt.savefig('plotSketchSizes.svg')
