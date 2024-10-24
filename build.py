import argparse
import os
import sys

from subprocess import Popen, PIPE


PLATFORM_GENERATOR = '\"Visual Studio 17\"'


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
        formatter_class = lambda prog: argparse.HelpFormatter(prog, max_help_position=100, width=200)
        description = 'This tool can be used to build and deploy the Instruments of the orchestra project.'
        epilog = ''
        parser = argparse.ArgumentParser(description=description, formatter_class=formatter_class, epilog=epilog)
        parser.add_argument('-p', '--prepare', action='store_true', help='prepares the project for use with IDE')
        parser.add_argument('-d', '--debug', action='store_true', help='prepare or build debug version')
        parser.add_argument('-b', '--build', action='store_true', help='build the project')

        self.args = parser.parse_args()
       
        self.version = ""

        path_project = os.path.dirname(os.path.realpath(__file__))
        self.args.path_project = path_project


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


    def _build_prepare(self):
        projectfolderVS =  os.path.join(self.args.path_project)
        buildFolder = os.path.join(projectfolderVS, "build")
        autoCWD = AutoCWD(projectfolderVS)
        
        packages_install_cmd = r"conan install packages --build missing -g CMakeToolchain -g CMakeDeps -of " + buildFolder + " --settings=build_type=" + BuildRunner.TARGET_CONFIG
        self._execute_command(packages_install_cmd, "Install Conan packages")
        
        prepare_cmd = f'cmake -G {PLATFORM_GENERATOR} -B build -DCMAKE_TOOLCHAIN_FILE=build/build/generators/conan_toolchain.cmake'
        prepare_cmd = f'cmake -G {PLATFORM_GENERATOR} -B build'
        self._execute_command(prepare_cmd, "Select build generator")
        
        del autoCWD

        
    def _build_project(self):
        projectfolderVS =  os.path.join(self.args.path_project)
        buildFolder = os.path.join(projectfolderVS, "build")

        if os.path.exists(projectfolderVS + "/CMakeCache.txt"):
            self._execute_command("cmake --build " + projectfolderVS + " --target clean", "Run CMake clean")
        
        self._execute_command("cmake --build " + buildFolder + " --config " + BuildRunner.TARGET_CONFIG + " --clean-first ", "Build Instruments of the Orchestra")    


        
    def doit(self):
        if self.args.debug:
            BuildRunner.TARGET_CONFIG = 'Debug'
        if self.args.prepare:
            self._build_prepare()
        if self.args.build:
            self._build_prepare()
            self._build_project()

            
if __name__ == '__main__':
    BuildRunner().doit()

