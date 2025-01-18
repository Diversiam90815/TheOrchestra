import os
import re

SAMPLES_DIR  = os.path.join(os.getcwd(), "Assets", "Samples")

NOTE_REGEX = re.compile(r'^[A-Ga-g][#b]?\d+$')  # Regex to detect note patterns like "B2", "C#3","Db4",..

VALID_DYNAMICS = {"p", "pp", "ppp", "f", "ff", "fff", "mp", "mf"}


def rename_samples(samples_dir):
    for root, dirs, files in os.walk(samples_dir):
        for file in files:

            if not file.lower().endswith(".wav"):
                continue

            old_path = os.path.join(root, file)
            name_no_ext = os.path.splitext(file)[0]
            parts = name_no_ext.split('_')

            # Try to detect note, dynamic, rr from the parts:
            note_found = None
            dynamic_found = None
            rr_found = None

            leftover_tokens = []

            for part in parts:
                # Note Check
                if(note_found is None and NOTE_REGEX.match(part)):
                        note_found = part
                        continue

                # Dynamic Check - if it starts with v and remainder is digit
                #                   or if it is in VALID_DYNAMICS
                if dynamic_found is None:
                    if part in VALID_DYNAMICS:
                        dynamic_found = part
                        continue
                    elif part.startswith('v') and part[1:].isdigit():
                        dynamic_found = part
                        continue                    
                
                # Round Robbin Check - might be "rr1", "2", or just "Main" (1 rr layer),...
                if rr_found is None:
                    #if rrX
                    if part.startswith("rr") and part[2:].isdigit():
                        rr_found = part[2:]
                        continue
                    
                    # if just digit
                    elif part.isdigit():
                        rr_found = part
                        continue

                    # if it is Main
                    elif part.lower() == "main":
                        rr_found = "1"
                        continue

                    # Else we guess it's not rr
                    leftover_tokens.append(part)
                
                else:
                    leftover_tokens.append(part)
        
                # If we never found a round-robin, default to "1"
                if rr_found is None:
                    rr_found = "1" 

                # At least we need a note and dynamic. If missing, skip rename
                if not note_found or not dynamic_found:
                    print(f"Skipping rename for {old_path} due to missing note / dynamic!")
                    continue

                # Build new filename
                new_filename = f"{note_found}_{dynamic_found}_{rr_found}.wav"
                new_path = os.path.join(root, new_filename)

                # If it does not actually change, skip
                if new_path == old_path:
                    print(f"No rename needed for {old_path}")
                    continue
                
                # if a file with that name already exists, skip
                if os.path.exists(new_path):
                    print(f"Cannot rename {old_path} -> {new_filename}, target already exists.")
                    continue

                # Rename
                os.rename(old_path, new_path)
                print(f"Renamed:\n\t{old_path}\n=>\n\t{new_path}")


if __name__ == "__main__":
    rename_samples(SAMPLES_DIR)
    print("Renaming Samples in directory done!")

