import matplotlib.pyplot as plt
import networkx as nx

class TreeNode:
    def __init__(self, key, pokemons=None):
        self.key = key
        self.left = None
        self.right = None
        self.pokemons = pokemons if pokemons is not None else []

def insert(root, key, pokemon):
    if root is None:
        return TreeNode(key, [pokemon])
    elif key < root.key:
        root.left = insert(root.left, key, pokemon)
    elif key > root.key:
        root.right = insert(root.right, key, pokemon)
    else:
        root.pokemons.append(pokemon)
    return root

def plot_tree(root, pos=None, x=0, y=0, layer_height=20, ax=None):
    if pos is None:
        pos = {}
    if ax is None:
        fig, ax = plt.subplots()
    pos[root.key] = (x, y)
    ax.text(x, y, f"HP: {root.key}\nPokemons: {', '.join([pokemon['Name'] for pokemon in root.pokemons])}", ha='center', va='center', bbox=dict(facecolor='lightgray', edgecolor='black'))
    if root.left:
        pos = plot_tree(root.left, pos, x - layer_height, y - layer_height, layer_height / 2, ax)
        ax.plot([x, x - layer_height], [y - layer_height, y - layer_height], '-k')
    if root.right:
        pos = plot_tree(root.right, pos, x + layer_height, y - layer_height, layer_height / 2, ax)
        ax.plot([x, x + layer_height], [y - layer_height, y - layer_height], '-k')
    return pos

# Create a sample binary search tree based on HP
pokemon_data = [
    {"Name": "Bulbasaur", "HP": 45},
    {"Name": "Ivysaur", "HP": 60},
    {"Name": "Venusaur", "HP": 80},
    {"Name": "Charizard", "HP": 78},
    {"Name": "Squirtle", "HP": 44},
    # Add more Pokemon data as needed
]

root_node = None
for pokemon in pokemon_data:
    root_node = insert(root_node, pokemon["HP"], pokemon)

# Plot the tree
plt.figure(figsize=(10, 8))
plot_tree(root_node)
plt.title("Binary Search Tree of Pokemon HP")
plt.show()