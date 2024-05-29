"""
This is a python script to filter and edit the audio samples in the Asset folder
"""

import os
import re
from pathlib import Path

# Get the directory where the current script is located
current_directory = Path(__file__).resolve().parent

samples_dir = os.path.join(current_directory, "Assets", "Samples")

# Round robin indices to keep
valid_round_robin_indices = ['1', '05', '15', '25']
valid_articulations = ['normal', 'long']

# Function to process files
def process_files(samples_dir):
    for instrument in os.listdir(samples_dir):
        instrument_path = os.path.join(samples_dir, instrument)
        if os.path.isdir(instrument_path):
            for sample in os.listdir(instrument_path):
                sample_path = os.path.join(instrument_path, sample)
                process_file(sample_path)


# Function to process each file
def process_file(file_path):
    filename = os.path.basename(file_path)

    # Check if the file contains valid round robin factor
    match = re.search(r'_(\d+)_', filename)
    if not match or match.group(1) not in valid_round_robin_indices:
        os.remove(file_path)
        print(f"Deleted (invalid round robin): {file_path}")
        return

    # Parse filename to get parts
    parts = filename.split('_')
    if len(parts) < 5:
        return  # Invalid file name format, skip

    note = parts[1]
    round_robin = parts[2]
    dynamic = parts[3]
    articulation = parts[4].split('.')[0]  # Remove file extension

    # Delete files with invalid articulations
    if articulation not in valid_articulations:
        os.remove(file_path)
        print(f"Deleted (invalid articulation): {file_path}")
        return

    # Create new filename without instrument name and articulation
    new_filename = f"{note}_{round_robin}_{dynamic}.mp3"
    new_file_path = os.path.join(os.path.dirname(file_path), new_filename)

    # Check if new file name already exists to avoid FileExistsError
    if not os.path.exists(new_file_path):
        os.rename(file_path, new_file_path)
        print(f"Renamed: {file_path} to {new_file_path}")
    else:
        os.remove(file_path)
        print(f"Deleted (duplicate after renaming): {file_path}")

# Run the script
if __name__ == '__main__':
    process_files(samples_dir)
