<h1 align="center">
 <img src="https://mp3tag.app/assets/images/mp3tag-logo.png" width="256" height="256">
 <br>
 Mp3tag Web Sources Scripts
 <br>
 <br>
 <a href="https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/LICENSE">
  <img src="https://img.shields.io/badge/License-MIT-181717?style=for-the-badge&logo=github">
 </a>
 <a href="https://mp3tag.app/">
  <img src="https://img.shields.io/badge/macOS-Mp3tag%20v1.6.0%20or%20above-000000?style=for-the-badge&logo=macOS">
 </a>
 <a href="https://www.mp3tag.de/en/">
  <img src="https://img.shields.io/badge/Windows-Mp3tag%20v3.06b%20or%20above-0078D6?style=for-the-badge&logo=windows">
 </a>
</h1>

## Table of Contents
* [Information](#information)
  * [Description](#description)
  * [Status](#status)
* [Step-by-Step Instructions on Adding Web Sources Scripts to Mp3tag](#step-by-step-instructions-on-adding-web-sources-scripts-to-mp3tag)
  * [macOS](#macos)
  * [Windows](#windows)
* [Step-by-Step Instructions on Using Web Sources Scripts in Mp3tag](#step-by-step-instructions-on-using-web-sources-scripts-in-mp3tag)
  * [macOS](#macos-1)
  * [Windows](#windows-1)
* [Commented-Out Tag Fields in the Web Sources Scripts](#commented-out-tag-fields-in-the-web-sources-scripts)
* [Questions About the Web Sources Scripts](#questions-about-the-web-sources-scripts)
  * [How do I change the purchasing country?](#q-how-do-i-change-the-purchasing-country)
  * [How do I complete the XID tag field?](#q-how-do-i-complete-the-xid-tag-field)
  * [How do I get a genre ID that is not listed in the web sources scripts?](#q-how-do-i-get-a-genre-id-that-is-not-listed-in-the-web-sources-scripts)
  * [How do I get music metadata from a country of Apple Music or iTunes Store that is not available in this repository?](#q-how-do-i-get-music-metadata-from-a-country-of-apple-music-or-itunes-store-that-is-not-available-in-this-repository)
* [Additional Information](#additional-information)
* [License](#license)

## Information
### Description
This repository contains web sources scripts for Mp3tag that will allow for the databases of Apple Music and the iTunes Store to be used to update music metadata. These web sources scripts for Mp3tag can automatically add tags to any song available on Apple Music and/or the iTunes Store. For these web sources scripts to work, the Apple Music or iTunes Store URL of a song is needed, which can be easily obtained by clicking on "Copy Link" in Apple Music or the iTunes Store.

The web sources scripts in this repository include some modifications that were made by me. The original web sources scripts without any of these modifications can be located at a forum called [Mp3tag Community](https://community.mp3tag.de/). Special thanks to [AreDigg on Mp3tag Community](https://community.mp3tag.de/t/ws-apple-music/51184) for making the original versions of the Apple Music and iTunes Store web sources scripts.

### Status
- Apple Music Web Sources Script: `Working`
- iTunes Store Web Sources Script: `Working`

## Step-by-Step Instructions on Adding Web Sources Scripts to Mp3tag
### macOS
1. Download Mp3tag from the official website ([Official Version](https://mp3tag.app/get/))
2. Install Mp3tag on your macOS device and open it
3. Download the web sources scripts from this repository
4. Click on "Tag Sources" in the menu bar
5. Click on "Open Tag Sources Folder"
6. Drag and drop the web sources scripts into the "Sources" folder that is opened by the application
### Windows
1. Download Mp3tag from the official website ([Official Version](https://www.mp3tag.de/en/download.html) or [Beta Version](https://community.mp3tag.de/t/mp3tag-development-build-status/455))
2. Install Mp3tag on your Windows device and open it
3. Download the web sources scripts from this repository
4. Move the **.inc** and **.src** files to `%appdata%\mp3tag\data\sources`

## Step-by-Step Instructions on Using Web Sources Scripts in Mp3tag
### macOS
1. Open Mp3tag
2. Select the song(s) that you want to retrieve metadata for
3. Click on "Tag Sources" in the menu bar
4. Hover over Apple Music or iTunes Store
5. Select the country that you want to get your metadata from
6. Paste an Apple Music or iTunes Store URL into the text box
7. Click on "Search"
8. Select the correct album
9. Click on "Next"
10. Compare the bottom two boxes and check if your song(s) is/are in the right order/placement
11. Click on "Merge" or "Save" to complete the process
### Windows
1. Open Mp3tag
2. Select the song(s) that you want to retrieve metadata for
3. Click on "Tag Sources" in the toolbar
4. Hover over Apple Music or iTunes Store
5. Select the country that you want to get your metadata from
6. Paste an Apple Music or iTunes Store URL into the text box
7. Click on "Next >"
8. Check if it is the correct album
9. Compare the bottom two boxes and check if your song(s) is/are in the right order/placement
10. Click on "OK" to complete the process

## Commented-Out Tag Fields in the Web Sources Scripts
There are three commented-out tag fields in these web sources scripts because these three tag fields will contain your personal information and will have to be edited by you. The three commented-out tag fields are the following: `ITUNESACCOUNT`, `ITUNESOWNER`, and `ITUNESPURCHASEDATE`. You can leave these commented-out codes alone if you do not want to attach your personal information to your songs.

`ITUNESACCOUNT` - Your Email Address
<br>
`ITUNESOWNER` - Your Name
<br>
`ITUNESPURCHASEDATE` - Date of Purchase (Year-Month-Day Hour:Minute:Second)

## Questions About the Web Sources Scripts
#### Q: How do I change the purchasing country?
A: For these web sources scripts in this repository, the default purchasing country is the United States. If you do not want the United States to be the purchasing country, you will have to change the iTunes storefront ID in the .inc file. You can find the iTunes storefront ID in the .inc file by searching for the line that has `ITUNESCOUNTRYID` in it. After finding that line, you should look at the next line. Now, you will be able to change the purchasing country by deleting "143441" and then adding a different iTunes storefront ID. To find the iTunes storefront IDs, you can click on this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Country%20Codes%20and%20Storefront%20IDs.csv).

*Purchasing Country Example (Germany):*
<br>
```
OutputTo "ITUNESCOUNTRYID"
Say "143443"
Say "|"
```

#### Q: How do I complete the XID tag field?
A: The Apple Music web sources script only gets the International Standard Recording Code (ISRC) for the XID tag field. Two other parts are needed to complete the XID tag field. One of those parts is the content provider, which is the company that distributes the music. To get the content provider, you will have to search for them online, but I have listed some common content providers in this [text file](https://github.com/MrBukLau/mp3tag-web-sources-scripts/raw/main/Information/iTunes%20XID.txt). The other part is just the word ISRC in lowercase letters. In total, there are three parts to the XID tag field, and they are separated from each other by colons.

*XID Format:*
<br>
**Content Provider**:isrc:**Actual ISRC**

*XID Example:*
<br>
```
SonyBMG:isrc:USSM19922509
```

#### Q: How do I get a genre ID that is not listed in the web sources scripts?
A: Some of the most common genre IDs are already accounted for in these web sources scripts. However, if there is a genre ID that is not listed in web sources scripts, you can add that genre ID in the .inc file by searching for the line that says `ITUNESGENREID` and following the same format as the other genre IDs. To find more genre IDs, you can click on this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Genre%20IDs.csv). If you are using the link that I provided in the previous sentence, you should make sure that you are looking at [category #34](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Genre%20IDs.csv#L37) because this category is the one that contains the genre IDs for music.

#### Q: How do I get music metadata from a country of Apple Music or iTunes Store that is not available in this repository?
A: You will have to go to the .src file and change the country code in it. To find the country codes, you can click on this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Country%20Codes%20and%20Storefront%20IDs.csv) or this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Country%20Codes.md). Also, you are able to change the language of the music metadata by changing the language parameter (`l` for Apple Music and `lang` for iTunes Store) in that same place.

*Country Code Example for Apple Music Script (Germany):*
<br>
```
[IndexUrl]=https://music.apple.com/de/search?l=en&term=%s
```

*Country Code Example for iTunes Store Script (Germany):*
<br>
```
[IndexUrl]=https://itunes.apple.com/search?country=de&lang=en_us&entity=album&term=%s
[AlbumUrl]=https://itunes.apple.com/lookup?country=de&lang=en_us&entity=song&limit=200&id=
```

## Additional Information
* To find more web sources scripts for Mp3tag, click on this [link](https://community.mp3tag.de/c/development/web-sources-scripts/12)
* To learn more about how to use web sources scripts in Mp3tag, click on this [link](https://github.com/jonaaa20/itunes-web-sources)
* To learn more about the APIs, [click here for the Apple Music API](https://developer.apple.com/documentation/applemusicapi/) and [click here for the iTunes Store API](https://developer.apple.com/library/archive/documentation/AudioVideo/Conceptual/iTuneSearchAPI/index.html)
* To learn more about the syntax of these web sources scripts for Mp3tag, click on this [link](https://docs.mp3tag.de/tag-sources/development/)
* To learn more about the tag fields in Mp3tag, click on this [link](https://docs.mp3tag.de/mapping/)
* To learn more about the XID tag field, click on this [link](https://community.mp3tag.de/t/support-for-itunesalbumadvisory-field/51715/10)

## License
[MIT](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/LICENSE)
