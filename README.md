<h1 align="center">
 <br>
 <img src="https://www.mp3tag.de/images/logo.png">
 <br>
 Mp3tag Web Sources Scripts
 <br>
 <a href="https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/LICENSE"><img src="https://img.shields.io/badge/License-MIT-blue.svg"></a>
 <a href="https://www.mp3tag.de/en/index.html"><img src="https://img.shields.io/badge/Program-Mp3tag-orange.svg"></a>
</h1>

<p align="center">
 <b>
 IMPORTANT NOTICE: You need to download Mp3tag v3.06b or above for the new iTunes tags to work properly.
 </b>
</p>

## Table of Contents
* [Description](https://github.com/MrBukLau/mp3tag-web-sources-scripts#description)
* [Instructions on Adding Web Sources Scripts to Mp3tag](https://github.com/MrBukLau/mp3tag-web-sources-scripts#instructions-on-adding-web-sources-scripts-to-mp3tag)
* [Questions About the Web Sources Scripts](https://github.com/MrBukLau/mp3tag-web-sources-scripts#questions-about-the-web-sources-scripts)
  * [How do I change the purchasing country?](https://github.com/MrBukLau/mp3tag-web-sources-scripts#q-how-do-i-change-the-purchasing-country)
  * [How do I get a genre ID that is not listed in the web sources scripts?](https://github.com/MrBukLau/mp3tag-web-sources-scripts#q-how-do-i-get-a-genre-id-that-is-not-listed-in-the-web-sources-scripts)
  * [How do I get music metadata from a different country of Apple Music or iTunes Store?](https://github.com/MrBukLau/mp3tag-web-sources-scripts#q-how-do-i-get-music-metadata-from-a-different-country-of-apple-music-or-itunes-store)
* [Additional Information](https://github.com/MrBukLau/mp3tag-web-sources-scripts#additional-information)
* [License](https://github.com/MrBukLau/mp3tag-web-sources-scripts#license)

## Description
This repository contains web sources scripts for Mp3tag that will allow you to use Apple Music or the iTunes Store to update music metadata. These web sources scripts for Mp3tag can automatically add tags to any song if that song is available on Apple Music and/or the iTunes Store. For these web sources scripts to work, the Apple Music or iTunes Store URL of a song is needed, which can be obtained by clicking on "Copy Link" in Apple Music or the iTunes Store.

The web sources scripts in this repository include some modifications that were written by me. The original web sources scripts without any of these modifications can be located at a forum called [Mp3tag Community](https://community.mp3tag.de/).

## Instructions on Adding Web Sources Scripts to Mp3tag
1. Download Mp3tag from the official website ([Official Version](https://www.mp3tag.de/en/download.html) or [Beta Version](https://community.mp3tag.de/t/mp3tag-development-build-status/455))
2. Install Mp3tag on your device and open it
3. Download the web sources scripts from this repository
4. Move the **.inc** and **.src** files to **%appdata%\mp3tag\data\sources**

## Questions About the Web Sources Scripts
#### Q: How do I change the purchasing country?
A: The default purchasing country is the United States. To change the default purchasing country, you will have to go to the .inc file and search for the line that has "ITUNESCOUNTRYID" in it. Below this line, you will see 143441, which is the iTunes storefront ID of the United States. You can change this storefront ID to the storefront ID of the country you want it to be, and you can find these storefront IDs of different countries at this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Country%20Codes%20and%20Storefront%20IDs.csv) and this [link](https://gist.github.com/hmml/8942940).

*Example Using Germany as the Purchasing Country:* <br>
```
OutputTo "ITUNESCOUNTRYID"
Say "143443"
Say "|"
```

#### Q: How do I get a genre ID that is not listed in the web sources scripts?
A: Some of the most common genre IDs are already accounted for in these web sources scripts. However, if there is a genre ID that is not listed in web sources scripts, you can add that genre ID in the .inc file by searching for the line that says "ITUNESGENREID" and following the same format as the other genre IDs. To find more genre IDs, you can click on this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Genre%20IDs.csv).

#### Q: How do I get music metadata from a different country of Apple Music or iTunes Store?
A: You will have to go to the .src file and change the country code in it. To find country codes, you can click on this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Country%20Codes%20and%20Storefront%20IDs.csv) or this [link](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/Information/iTunes%20Country%20Codes.md).

*Example Using Germany as the Country Code:* <br>
```
[IndexUrl]=https://itunes.apple.com/search?media=music&entity=album&limit=200&country=de&lang=en_us
```

## Additional Information
* For information about the syntax of these web sources scripts, click on this [link](https://help.mp3tag.de/main_online.html)
* For instructions on how to use web sources scripts in Mp3tag, click on this [link](https://github.com/jonaaa20/itunes-web-sources)
* To find more web sources scripts for Mp3tag, click on this [link](https://community.mp3tag.de/c/development/web-sources-scripts/12)
* To learn more about the APIs, [click here for the Apple Music API](https://developer.apple.com/documentation/applemusicapi/) and [click here for the iTunes Store API](https://affiliate.itunes.apple.com/resources/documentation/itunes-store-web-service-search-api/)
* To view the original web sources scripts, [click here for the Apple Music script](https://community.mp3tag.de/t/ws-apple-music/51184) and [click here for the iTunes Store script](https://community.mp3tag.de/t/ws-itunes/13478)

## License
[MIT](https://github.com/MrBukLau/mp3tag-web-sources-scripts/blob/main/LICENSE)
