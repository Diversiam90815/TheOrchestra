import os
import re

# Main folder where each subfolder might be "Woodwinds", "Strings", "Brass", etc.
SAMPLES_DIR = os.path.join(os.getcwd(), "Assets", "Samples")

NOTE_REGEX = re.compile(r'^[A-Ga-g][#b]?\d+$')  # e.g. B2, C#3, etc.
VALID_DYNAMICS = {"p", "pp", "ppp", "f", "ff", "fff", "mp", "mf"}
DEFAULT_DYNAMIC = "mf"
DEFAULT_RR      = "1"

def rename_in_folder(folder_path):
    """
    Rename all .wav files in the given folder and *its* subfolders
    according to the note/dynamic/round-robin pattern.
    """
    for root, _, files in os.walk(folder_path):
        for filename in files:
            if not filename.lower().endswith(".wav"):
                continue

            old_path = os.path.join(root, filename)
            name_no_ext = os.path.splitext(filename)[0]
            parts = name_no_ext.split('_')

            note_found    = None
            dynamic_found = None
            rr_found      = None

            # Parse all parts
            for part in parts:
                lower_part = part.lower()

                # 1) Note
                if note_found is None and NOTE_REGEX.match(part):
                    note_found = part
                    continue

                # 2) Dynamic
                if dynamic_found is None:
                    if lower_part in VALID_DYNAMICS:
                        dynamic_found = lower_part
                        continue
                    elif lower_part.startswith('v') and lower_part[1:].isdigit():
                        dynamic_found = lower_part
                        continue

                # 3) Round Robin
                if rr_found is None:
                    if lower_part.startswith("rr") and lower_part[2:].isdigit():
                        rr_found = lower_part[2:]
                        continue
                    elif lower_part.isdigit():
                        rr_found = lower_part
                        continue

            # Set defaults
            if dynamic_found is None:
                dynamic_found = DEFAULT_DYNAMIC
            if rr_found is None:
                rr_found = DEFAULT_RR

            # Must have a note
            if not note_found:
                # skip
                continue

            new_filename = f"{note_found}_{dynamic_found}_{rr_found}.wav"
            new_path     = os.path.join(root, new_filename)

            if new_path == old_path:
                continue
            if os.path.exists(new_path):
                continue

            os.rename(old_path, new_path)



def rename_samples(samples_dir):
    """
    For each *section folder* (e.g. 'Woodwinds', 'Strings', etc.) 
    in SAMPLES_DIR, rename its contents, then print 'Done' once complete.
    """
    for section_name in os.listdir(samples_dir):
        section_path = os.path.join(samples_dir, section_name)
        if not os.path.isdir(section_path):
            continue

        print(f"Processing folder : {section_name}...", end="", flush=True)
        rename_in_folder(section_path)
        print("Done!")



if __name__ == "__main__":
    rename_samples(SAMPLES_DIR)
    print("Renaming Samples in directory done!")

