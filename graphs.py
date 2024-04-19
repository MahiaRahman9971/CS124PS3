import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('results.csv')

# Reordering the columns as specified
column_order = ['KK', 'RR Standard', 'HC Standard', 'SA Standard', 'RR Prepartitioned', 'HC Prepartitioned', 'SA Prepartitioned']
data = data[column_order]

# Setting up the plot
plt.figure(figsize=(14, 8))
boxprops = dict(linestyle='-', linewidth=2, color='darkblue')
whiskerprops = dict(linestyle='--', linewidth=2, color='orange')
capprops = dict(linestyle='-', linewidth=2, color='black')
medianprops = dict(linestyle='-', linewidth=2.5, color='orange')
flierprops = dict(marker='o', markersize=12, linestyle='none')

data.boxplot(column=column_order,
             boxprops=boxprops, whiskerprops=whiskerprops, capprops=capprops,
             medianprops=medianprops, flierprops=flierprops, patch_artist=True)

plt.title('Algorithm Residue Comparisons', fontsize=16, fontweight='bold')
plt.ylabel('Residue (Log Scale)', fontsize=14)
plt.xlabel('Algorithms', fontsize=14)
plt.xticks(rotation=45, fontsize=12)
plt.yscale('log')  # Using logarithmic scale due to wide range of values
plt.grid(True, linestyle='--', alpha=0.6)

# Show the plot
plt.tight_layout()
plt.show()
