import os
import sys

from scripts.paths import *
from scripts.build_runner import BuildRunner
from scripts.argument_parser import create_argument_parser


def main():
    parser = create_argument_parser()
    args = parser.parse_args()

    if not len(sys.argv) > 1:
        parser.print_help()
        exit(1)

    ''' Setting up environment '''
    os.chdir(ROOT_DIR)

    build_dir = get_build_dir(str(args.configuration), str(args.architecture))
    runner = BuildRunner(root_dir=ROOT_DIR, build_dir=build_dir, project_name="The Orchestra")

    runner.update_environment()
    runner.update_app_version()

    print("==== The Orchestra Configuration ====")
    print(f"Current Directory:   {ROOT_DIR}")
    print(f"Build Directory:     {build_dir}")
    print(f"Architecture:        {args.architecture}")
    print(f"Configuration:       {args.configuration}")
    print(f"Environment:         {runner.env}")
    print(f"Version:             {runner.version}")
    print("=====================================")

    runner.create_build_generator(
        platform=args.platform,
        build=args.build,
        architecture=args.architecture,
        configuration=args.configuration,
    )

    if not args.prepare:
        runner.run_cpp_unit_tests(configuration=args.configuration)


if __name__ == "__main__":
    main()