#include "ResourcePath.hpp"

#include <CoreFoundation/CoreFoundation.h>
#include <filesystem>
#include <limits.h>

std::string resourcePath(const std::string &relativePath)
{
    CFBundleRef bundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(bundle);

    char path[PATH_MAX];

    CFURLGetFileSystemRepresentation(
        resourcesURL,
        true,
        reinterpret_cast<UInt8 *>(path),
        sizeof(path));

    CFRelease(resourcesURL);

    return (std::filesystem::path(path) / relativePath).string();
}
