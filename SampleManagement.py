import os
import re
from pathlib import Path

# Get the directory where the current script is located
current_directory = Path(__file__).resolve().parent

samples_dir = os.path.join(current_directory, "Assets", "Samples")

# Round robin indices to keep and their mappings
valid_round_robin_indices = {'1': '1', '05': '2', '15': '3', '25': '4'}
valid_articulations = ['normal', 'long', 'arco-normal']

# Dynamic mappings
dynamic_mappings = {
    'pianissimo': 'pp',
    'piano': 'p',
    'mezzo-piano': 'mp',
    'mezzo-forte': 'mf',
    'forte': 'f',
    'fortissimo': 'ff'
}

# Instruments to exclude from the process
excluded_instruments = []

# Notes to delete
notes_to_delete = ['As', 'Cs', 'Ds', 'Fs', 'Gs']

# Function to process files
def process_files(samples_dir):
    for section in os.listdir(samples_dir):
        section_dir = os.path.join(samples_dir, section)
        if not os.path.isdir(section_dir):
            continue
        for instrument in os.listdir(section_dir):
            instrument_path = os.path.join(section_dir, instrument)
            if os.path.isdir(instrument_path):
                if instrument in excluded_instruments:
                    print(f"Skipping excluded instrument: {instrument}")
                    continue  # Skip excluded instruments
                for sample in os.listdir(instrument_path):
                    sample_path = os.path.join(instrument_path, sample)
                    process_file_with_new_naming(sample_path)


# Function to process each file
def process_file_with_old_naming(file_path):
    filename = os.path.basename(file_path)

    # Check if the file contains valid round robin factor
    match = re.search(r'_(\d+)_', filename)
    if not match:
        print(f"No round robin match: {filename}")
        return
    round_robin_key = match.group(1)
    if round_robin_key not in valid_round_robin_indices:
        os.remove(file_path)
        print(f"Deleted (invalid round robin): {file_path}")
        return

    # Parse filename to get parts
    parts = filename.split('_')
    if len(parts) < 3:
        print(f"Invalid file name format: {filename}")
        return  # Invalid file name format, skip

    note = parts[1]
    round_robin = valid_round_robin_indices[round_robin_key]
    dynamic = parts[3]
    articulation = parts[4].split('.')[0]  # Remove file extension

    # Delete files with invalid articulations
    if articulation not in valid_articulations:
        os.remove(file_path)
        print(f"Deleted (invalid articulation): {file_path}")
        return

    # Delete files with specific notes (regardless of octave)
    note_name = re.match(r'[A-Ga-g][s#]?', note)
    if note_name and note_name.group() in notes_to_delete:
        os.remove(file_path)
        print(f"Deleted (excluded note): {file_path}")
        return

    # Map dynamics to desired format
    dynamic = dynamic_mappings.get(dynamic, dynamic)

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


# Function to process each file
def process_file_with_new_naming(file_path):
    filename = os.path.basename(file_path)

    # Parse filename to get parts
    parts = filename.split('_')
    if len(parts) < 3:
        print(f"Invalid file name format: {filename}")
        return  # Invalid file name format, skip

    note = parts[0]
    round_robin = parts[1]
    dynamic = parts[2].split('.')[0]  # Remove file extension

    # Delete files with specific notes (regardless of octave)
    note_name = re.match(r'[A-Ga-g][s#]?', note)
    if note_name and note_name.group() in notes_to_delete:
        os.remove(file_path)
        print(f"Deleted (excluded note): {file_path}")
        return
    


# Run the script
if __name__ == '__main__':
    process_files(samples_dir)
