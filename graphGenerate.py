import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Replace 'path_to_csv_file.csv' with the actual path to your CSV file
csv_file_path = 'path_to_csv_file.csv'

# Read the data into a DataFrame
df = pd.read_csv(csv_file_path)

# Plotting
fig, ax = plt.subplots()

# Generate a color map to handle different CPU counts dynamically
cpu_counts = df['CPUs'].unique()
colors = plt.cm.viridis(np.linspace(0, 1, len(cpu_counts)))
cpu_colors_map = dict(zip(cpu_counts, colors))

# Create a line plot for each group of CPUs
for key, grp in df.groupby(['CPUs']):
    # Sorting the values by MatrixSize to ensure the line is plotted correctly
    grp = grp.sort_values('MatrixSize')
    ax.plot(grp['MatrixSize'], grp['Time'], label=f'CPUs: {key}', color=cpu_colors_map[key], marker='o')

# Setting the logarithmic scale for both axes since the data spans several orders of magnitude
ax.set_xscale('log', base=2)
ax.set_yscale('log')

# Labels and title
ax.set_xlabel('Matrix Size')
ax.set_ylabel('Time (seconds)')
ax.set_title('Matrix Size vs Time for Different CPU counts')

# Legend
ax.legend()

# Show the plot
plt.show()
