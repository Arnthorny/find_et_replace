# Find and Replace Program

## 0x00.Table of contents

- [0x01 Introduction](#0x01-Introduction)
- [0x02 Environment](#0x02-Environment)
- [0x03 Installation](#0x03-Installation)
- [0x04 Usage](#0x04-Usage)

## 0x01 Introduction

This is a simple find and replace program implemented using the [C programming language](<https://en.wikipedia.org/wiki/C_(programming_language)>).

It uses a command line interface to cycle through occurences of a searched string.

The CLI will allow the user perform the following tasks:

- Find occurences of a given string
- Replace a given occurence or all occurences of search text.
- Undo a pending replace (Not yet implemented).
- Save changes to file after replacement is complete.

## 0x02 Environment

<!-- ubuntu -->

<a href="https://ubuntu.com/" target="_blank"> <img height="" src="https://img.shields.io/static/v1?label=&message=Ubuntu&color=E95420&logo=Ubuntu&logoColor=E95420&labelColor=2F333A" alt="Suite CRM"></a> <!-- vim --> <a href="https://www.vim.org/" target="_blank"> <img height="" src="https://img.shields.io/static/v1?label=&message=Vim&color=019733&logo=Vim&logoColor=019733&labelColor=2F333A" alt="Suite CRM"></a> <!-- git --> <a href="https://git-scm.com/" target="_blank"> <img height="" src="https://img.shields.io/static/v1?label=&message=Git&color=F05032&logo=Git&logoColor=F05032&labelColor=2F333A" alt="git distributed version control system"></a> <!-- github --> <a href="https://github.com" target="_blank"> <img height="" src="https://img.shields.io/static/v1?label=&message=GitHub&color=181717&logo=GitHub&logoColor=f2f2f2&labelColor=2F333A" alt="Github"></a> <!-- C --> <a href="https://en.wikipedia.org/wiki/C_(programming_language)" target="_blank"> <img height="" src="https://img.shields.io/static/v1?label=&message=C&color=181717&logo=C&logoColor=A8B9CC&labelColor=2F333A" alt="C"></a>

## 0x03 Installation

```bash
git clone https://github.com/Arnthorny/find_et_replace.git
```

change to the `find_et_replace` directory and run the command:

```bash
 make
```

## 0x04 Usage

```bash
./fetr file_name search_string [replace_string]
```
