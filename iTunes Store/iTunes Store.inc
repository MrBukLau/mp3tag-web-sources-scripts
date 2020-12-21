##################################################################################################
#                           iTunes Store Web Sources Script for Mp3tag                           #
##################################################################################################

##################################################################################################
#                                  FORMAT FOR ITUNES SEARCH API                                  #
##################################################################################################
[Name]=iTunes
[BasedOn]=https://itunes.apple.com/
[WordSeparator]=%20
[IndexFormat]=%_preview%|%_url%|%Artist%|%Album%|%Explicitness%|%Year%|%Tracks%|%Copyright%
[Encoding]=url-utf-8

##################################################################################################
#                                        MAIN INFORMATION                                        #
##################################################################################################
[ParserScriptIndex]=...

findline "wrapperType\""

do
	joinuntil "}"
	replace "\\\"" "&quot;"
	replace "?uo=4" ""	  

	# PREVIEW
	findline "\"collectionViewUrl\":\""
	findinline "\"collectionViewUrl\":\""
	sayuntil "\", \""
	say "|"

	# URL
	findline "\"collectionId\":"
	findinline "\"collectionId\":"
	sayuntil ", \""
	say "&entity=song&limit=200"
	say "|"

	# ARTIST
	findline "\"artistName\":\""
	findinline "\"artistName\":\""
	sayuntil "\", \""
	say "|"

	# ALBUM
	findline "\"collectionCensoredName\":\""
	findinline "\"collectionCensoredName\":\""
	sayuntil "\", \""
	say "|"

	# EXPLICITNESS
	replace "notExplicit" "Not Explicit"
	replace "explicit" "Explicit"
	replace "cleaned" "Cleaned"
	findline "\"collectionExplicitness\":\""
	findinline "\"collectionExplicitness\":\""
	sayuntil "\", \""
	say "|"

	# YEAR
	findline "\"releaseDate\":\""
	findinline "\"releaseDate\":\""
	sayuntil "-"
	say "|"

	# TRACKS
	findline "\"trackCount\":"
	findinline "\"trackCount\":"
	sayuntil ", \""
	say "|"

	# COPYRIGHT
	findline "\"copyright\":\""
	findinline "\"copyright\":\""
	sayuntil "\", \""
	say "|"

	saynewline
	findline "wrapperType\"" 2 1
while "{\"wrapperType" 201

##################################################################################################
#                                      ALBUM IDENTIFICATION                                      #
##################################################################################################
[ParserScriptAlbum]=...

findline "wrapperType\""
joinuntil "}"
replace "\\\"" "&quot;"
replace "?uo=4" ""

outputto "COVERURL"
replace "100x100bb" "2000x2000"
findline "\"artworkUrl100\":\""
findinline "\"artworkUrl100\":\""
sayuntil "\", \""

outputto "ALBUMARTIST"
findline "\"artistName\":\""
findinline "\"artistName\":\""
sayuntil "\", \""

outputto "COPYRIGHT"
findline "\"copyright\":\""
findinline "\"copyright\":\""
sayuntil "\", \""

outputto "ALBUM"
findline "\"collectionCensoredName\":\""
findinline "\"collectionCensoredName\":\""
sayuntil "\", \""

##################################################################################################
#                                      TRACK IDENTIFICATION                                      #
##################################################################################################
findline "wrapperType\"" 2 1

do
	joinuntil "}"
	replace "\\\"" "&quot;"
	replace "?uo=4" ""

	outputto "TRACKS"
	findline "\"trackCensoredName\":\""
	findinline "\"trackCensoredName\":\""
	sayuntil "\", \""
	say "|"

	outputto "ARTIST"
	findline "\"artistName\":\""
	findinline "\"artistName\":\""
	sayuntil "\", \""
	say "|"

	outputto "YEAR"
	findline "\"releaseDate\":\""
	findinline "\"releaseDate\":\""
	sayuntil "\", \""
	say "|"

	outputto "GENRE"
	findline "\"primaryGenreName\":\""
	findinline "\"primaryGenreName\":\""
	sayuntil "\""
	say "|"

	outputto "_LENGTH"
	findline "\"trackTimeMillis\":"
	findinline "\"trackTimeMillis\":"
	sayuntil ", \""
	say "|"

	outputto "TRACK"
	findline "\"trackNumber\":"
	findinline "\"trackNumber\":"
	sayuntil ", \""
	say "|"

	outputto "DISCNUMBER"
	findline "\"discNumber\":"
	findinline "\"discNumber\":"
	sayuntil ", \""
	say "|"

	outputto "ITUNESADVISORY"
	replace "notExplicit" "0"
	replace "explicit" "1"
	replace "cleaned" "2"
	findline "\"trackExplicitness\":\""
	findinline "\"trackExplicitness\":\""
	sayuntil "\", \""
	say "|"

	outputto "ITUNESCATALOGID"
	findline "\"trackId\":"
	findinline "\"trackId\":"
	sayuntil ", \""
	say "|"

	outputto "TOTALTRACKS"
	findline "\"trackCount\":"
	findinline "\"trackCount\":"
	sayuntil ", \""
	say "|"

	outputto "TOTALDISCS"
	findline "\"discCount\":"
	findinline "\"discCount\":"
	sayuntil ", \""
	say "|"

	outputto "ITUNESMEDIATYPE"
	replace "book" "Audiobook"
	replace "album" "Album"
	replace "coached-audio" "Coached Audio"
	replace "feature-movie" "Feature Movie"
	replace "interactive- booklet" "Interactive Booklet"
	replace "music-video" "Music Video"
	replace "pdf podcast" "PDF Podcast"
	replace "podcast-episode" "Podcast Episode"
	replace "software-package" "Software Package"
	replace "song" "Normal"
	replace "tv- episode" "TV Episode"
	replace "artist" "Artist"
	findline "\"kind\":\""
	findinline "\"kind\":\""
	sayuntil "\""
	say "|"

	findline "wrapperType\"" 2 1
while "{\"wrapperType"
