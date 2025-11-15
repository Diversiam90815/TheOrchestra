from enum import Enum


class Architecture(Enum):
    x64 = "x64"
    ARM64 = "ARM64"

    def __str__(self) -> str:
        return self.value


class Environment(Enum):
    Development = "ENV_DEVELOPMENT"
    Staging = "ENV_STAGING"
    Production = "ENV_PRODUCTION"

    def __str__(self) -> str:
        return self.value


class Configuration(Enum):
    Debug = "Debug"
    Release = "Release"
    RelWithDebInfo = "RelWithDebInfo"

    def __str__(self) -> str:
        return self.value


class Platform(Enum):
    Ninja = 'Ninja'
    VisualStudio2022 =  'Visual Studio 17 2022'
    XCode = 'Xcode'
    
    def __str__(self) -> str:
        return self.value