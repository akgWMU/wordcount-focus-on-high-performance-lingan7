import os
import random

# Configuration
num_files = 500
words_per_file = 5000
output_dir = "files"

# List of conjunctions to exclude
conjunctions = {"and", "or", "but", "nor", "for", "so", "yet"}

# Load a dictionary of English words
# macOS/Linux usually have /usr/share/dict/words
with open("/usr/share/dict/words", "r") as f:
    all_words = [word.strip().lower() for word in f.readlines()]

# Filter out conjunctions and very short words
filtered_words = [w for w in all_words if w not in conjunctions and len(w) > 2]

# Create output directory if not exists
os.makedirs(output_dir, exist_ok=True)

# Generate files
for file_idx in range(1, num_files + 1):
    words = random.choices(filtered_words, k=words_per_file)
    file_name = os.path.join(output_dir, f"file_{file_idx}.txt")
    with open(file_name, "w") as f:
        f.write(' '.join(words))
    if file_idx % 50 == 0:
        print(f"{file_idx} files generated...")

print(f"All {num_files} files generated in '{output_dir}' directory.")
