def main():
    filename = input("File name: ")
    extension = filename.strip().lower().split(".")
    extension.reverse()
    print(get_media_type(extension[0]))


def get_media_type(ext):
    match ext:
        case "gif":
            return "image/gif"
        case "jpg":
            return "image/jpeg"
        case "jpeg":
            return "image/jpeg"
        case "png":
            return "image/png"
        case "pdf":
            return "application/pdf"
        case "txt":
            return "text/plain"
        case "zip":
            return "application/zip"
        case _:
            return "application/octet-stream"


main()
