# MP3-Tag-Reader-Editor-ID3v2.3
A modular C project that reads and edits ID3v2.3 metadata from MP3 files.   Supports viewing and modifying tags such as Title, Artist, Album, Year, Comment, and Genre.

---

## 🧠 OVERVIEW
This project extracts metadata stored in the **ID3v2.3** header of an MP3 file.  
It also provides the ability to edit selected frames directly by modifying the binary file.

The implementation includes:
- ID3 header parsing  
- Frame extraction (TIT2, TPE1, TALB, TYER, COMM, TCON)  
- Tag editing with binary overwrite  
- Validation for MP3 extension and ID3 presence  

---

## ✨ FEATURES

### ✔ View Tags  
Displays:  
- Title (TIT2)  
- Artist (TPE1)  
- Album (TALB)  
- Year (TYER / TDRC)  
- Comment (COMM)  
- Genre (TCON)  

### ✔ Edit Tags  
Allows editing of:
- `-t` Title  
- `-a` Artist  
- `-l` Album  
- `-y` Year  
- `-c` Comment  
- `-g` Genre  

Updates are written directly into the ID3v2.3 frame.

---

## 🔧 CONCEPTS USED
- ID3v2.3 specification  
- Binary file handling  
- Frame size decoding  
- Endianness handling  
- Pointer operations  
- Manual parsing of MP3 metadata  
- CLI-based metadata editor  

---

## 💡 FUTURE SCOPE
- Support for ID3v2.4 frames  
- Add UTF-8 decoding  
- Add new frame support (track number, album art, lyrics, etc.)  
- Export tag info to JSON or CSV  
- Build a GUI version  

---

## 📌 CONCLUSION
This project demonstrates an understanding of binary file processing, metadata formats, pointer manipulation, and modular C design. It provides a functional MP3 tag reader and editor modeled on real ID3 parsing utilities.
