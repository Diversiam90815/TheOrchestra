import argparse
import os
import sys
import re
import shutil

from subprocess import Popen, PIPE, check_output


class AutoCWD(object):
    """Auto restore directory"""

    def __init__(self, path=""):
        self.orgdir = os.getcwd()
        os.chdir(path)

    def __del__(self): 
        os.chdir(self.orgdir)


class BuildRunner(object):

    TARGET_CONFIG = 'Release'

    def __init__(self):   
        parser = argparse.ArgumentParser(description='This tool can be used to build and deploy the "The Orchestra" project.')
        parser.add_argument('-p', '--prepare', action='store_true', help='prepares the project for use with IDE')
        parser.add_argument('-d', '--debug', action='store_true', help='prepare or build debug version')
        parser.add_argument('-b', '--build', action='store_true', help='build the project')
        parser.add_argument('-v', '--version', action='store_true', help='display Python and CMake versions')

        self.args = parser.parse_args()
        self.platform = self._find_latest_visual_studio_version()
        self.version = ""
        self.args.path_project = os.path.dirname(os.path.realpath(__file__))


    @staticmethod
    def __log_description(description):
        print('{}{:80s}'.format('\t', description), end = '')
        sys.stdout.flush()


    @staticmethod
    def __log_done(msg='Done'):
        print(msg)
        

    def _execute_command(self, command, description):
        """ Execute system command and log stdout """
        BuildRunner.__log_description(description)
        
        execution = Popen(command, shell=True, stdout=PIPE, stderr=PIPE)
        output, error = execution.communicate()
        
        if execution.returncode:
            print('\n' + error.decode(encoding='utf-8', errors="replace"))
            print('\n' + output.decode(encoding='utf-8', errors="replace"))
            sys.stdout.flush()
            exit(1)

        BuildRunner.__log_done()

        sys.stdout.flush()
        result = output.decode(encoding='utf-8', errors="replace")

        return result


    def _find_latest_visual_studio_version(self):
        vswhere = os.path.join(os.environ.get("ProgramFiles(x86)"), "Microsoft Visual Studio", "Installer", "vswhere.exe")

        if not os.path.exists(vswhere):
            print("vswhere.exe not found! Using Visual Studio 2022 as default")
            return '\"Visual Studio 17\"'

        result = check_output([vswhere, '-latest', '-property', 'installationVersion'], shell=True).decode().strip()
        versionMatch = re.match(r'^(\d+)', result)

        if versionMatch:
            vsVersion = versionMatch.group(1)
            return f'\"Visual Studio {vsVersion}\"'

        else:
            print("Could not determine latest Visual Studio version. Using Visual Studio 2022 as default")
            return '\"Visual Studio 17\"'


    def _print_versions(self):
        """ Print Python, CMake & Projects versions """
        self._update_app_version()
        print(f"Project's version: {self.version}")
        print(f"Python version: {sys.version}")
        try:
            cmake_version = self._execute_command("cmake --version", "Get CMake version")
            print(f"CMake version: {cmake_version.splitlines()[0]}")  # print only the first line of output
        except Exception as e:
            print(f"Error retrieving CMake version: {e}")


    def _get_number_of_commits(self):
        autoCWD = AutoCWD(self.args.path_project)
        sys.stdout.flush()
        commit_hashes = check_output("git rev-list HEAD", shell=True).rstrip()
        commit_number = commit_hashes.count(b'\n') + 1
        del autoCWD
        return commit_number


    def _get_current_project_build_number(self):
        BuildNumber = self._get_number_of_commits()
        return BuildNumber
    

    def _get_current_project_version(self):
        cmake_file_path = os.path.join(self.args.path_project, "CMakeLists.txt")
        pattern = r'set\(ORCHESTRA_VERSION\s+(\d+\.\d+\.\d+)\)'

        with open(cmake_file_path, 'r') as f:
            for line in f:
                match = re.search(pattern, line)
                if match:
                    return match.group(1)
        return None


    def _update_app_version_in_cmake(self, project_version):
        pattern = r'set\(ORCHESTRA_VERSION\s+(\d+\.\d+\.\d+)\)'
        cmakeFile = os.path.join(self.args.path_project, "CMakeLists.txt")
        tmpFile = cmakeFile + '.tmp'

        with open (cmakeFile, 'r') as fileIn, open (tmpFile, 'w') as fileOut:
            for line in fileIn:
                match = re.search(pattern, line)
                if match:
                    fileOut.write(f'set(ORCHESTRA_VERSION {project_version})\n')
                else:
                    fileOut.write(line)

        shutil.move(tmpFile, cmakeFile)
        fileIn.close()
        fileOut.close()


    def _update_app_version(self):
        build_number = self._get_current_project_build_number()
        current_version = self._get_current_project_version()

        if current_version:
            version_parts = current_version.split('.')
            version_parts[-1] = str(build_number)
            self.version = '.'.join(version_parts)
            self._update_app_version_in_cmake(self.version)
            print(f"Set project version to {self.version}!")

        else:
            print("No version attribute found!")


    def _build_prepare(self):
        projectfolderVS =  os.path.join(self.args.path_project)
        autoCWD = AutoCWD(projectfolderVS)
        
        prepare_cmd = f'cmake -G {self.platform} -B build'
        self._execute_command(prepare_cmd, f"Select build generator : {self.platform}")
        
        del autoCWD

        
    def _build_project(self):
        projectfolderVS =  os.path.join(self.args.path_project)
        buildFolder = os.path.join(projectfolderVS, "build")

        if os.path.exists(projectfolderVS + "/CMakeCache.txt"):
            self._execute_command("cmake --build " + projectfolderVS + " --target clean", "Run CMake clean")
        
        self._execute_command("cmake --build " + buildFolder + " --config " + BuildRunner.TARGET_CONFIG + " --clean-first ", f"Build The Orchestra v{self.version}")    


        
    def doit(self):
        if self.args.version:
            self._print_versions()
        if self.args.debug:
            BuildRunner.TARGET_CONFIG = 'Debug'
        if self.args.prepare:
            self._build_prepare()
            self._update_app_version()
        if self.args.build:
            self._build_prepare()
            self._update_app_version()
            self._build_project()

            
if __name__ == '__main__':
    BuildRunner().doit()

