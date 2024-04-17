import pandas as pd
import matplotlib.pyplot as plt

# Load the data from CSV
data = pd.read_csv('results.csv')

# Function to plot each algorithm
def plot_algorithm(column_name, title, file_name):
    plt.figure(figsize=(10, 6))
    plt.plot(data['Instance'], data[column_name], label=title, marker='o', color='b')
    plt.title(f'{title} Performance Over Instances')
    plt.xlabel('Instance')
    plt.ylabel('Residue')
    plt.legend()
    plt.grid(True)
    plt.savefig(f'{file_name}.png')
    plt.show()

# Plotting each algorithm separately
plot_algorithm('KK', 'Karmarkar-Karp', 'karmarkar_karp')
plot_algorithm('RR Standard', 'Repeated Random Standard', 'repeated_random_standard')
plot_algorithm('RR Prepartitioned', 'Repeated Random Prepartitioned', 'repeated_random_prepartitioned')
plot_algorithm('HC Standard', 'Hill Climbing Standard', 'hill_climbing_standard')
plot_algorithm('HC Prepartitioned', 'Hill Climbing Prepartitioned', 'hill_climbing_prepartitioned')
plot_algorithm('SA Standard', 'Simulated Annealing Standard', 'simulated_annealing_standard')
plot_algorithm('SA Prepartitioned', 'Simulated Annealing Prepartitioned', 'simulated_annealing_prepartitioned')
