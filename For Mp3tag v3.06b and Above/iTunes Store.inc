# iTunes Store Web Sources Script for Mp3tag v3.06b and Above
[Name]=iTunes Store
[BasedOn]=https://music.apple.com/
[WordSeparator]=+
[IndexFormat]=%_url%|%Artist%|%Album%|%_preview%|%Version%|%Tracks%|%Copyright%|%Store%|%Year%|%Genre%
[Encoding]=url-utf-8

[ParserScriptIndex]=...

# debug "on" "C:\debug-index.txt"
# DebugWriteInput "C:\debug-index-in.txt"

json "on"

json_select "resultCount"
IfNot "0"
	json_foreach "results"
	json_select "collectionType"
	If "Album"

		json_select "collectionId"
		Say "&id="
		SayNextNumber
		Say "|"

		json_select "artistName"
		SayRest
		Say "|"

		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "collectionExplicitness"
		Replace "notExplicit" ""
		Replace "explicit" "Explicit"
		Replace "cleaned" "Cleaned"
		SayRest
		Say "|"

		json_select "trackCount"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "releaseDate"
		SayNextNumber
		Say "|"

		json_select "primaryGenreName"
		SayRest
		SayNewline

	EndIf
	If "Compilation"

		json_select "collectionId"
		Say "&id="
		SayNextNumber
		Say "|"

		json_select "artistName"
		SayRest
		Say "|"

		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"

		json_select "collectionViewUrl"
		Replace "?uo=4" ""
		Replace "&uo=4" ""
		SayRest
		Say "|"

		json_select "collectionExplicitness"
		Replace "notExplicit" "C"
		Replace "explicit" "C Explicit"
		Replace "cleaned" "C Cleaned"
		SayRest
		Say "|"

		json_select "trackCount"
		SayNextNumber
		Say "|"

		json_select "copyright"
		SayRest
		Say "|"

		json_select "country"
		SayRest
		Say "|"

		json_select "releaseDate"
		SayNextNumber
		Say "|"

		json_select "primaryGenreName"
		SayRest
		SayNewline

	EndIf
	json_foreach_end
EndIf

[ParserScriptAlbum]=...

# debug "on" "C:\debug-album.txt"
# DebugWriteInput "C:\debug-album-in.txt"

json "on"

json_select "resultCount"
IfNot "0"
	json_foreach "results"
	json_select "collectionType"
	If "Album"

		OutputTo "ITUNESALBUMID"
		json_select "collectionId"
		SayNextNumber

		OutputTo "ALBUMARTIST"
		json_select "artistName"
		If "Various Artists"
			OutputTo "COMPILATION"
			Say "1"
		Else
			SayRest
		EndIf

		OutputTo "ALBUM"
		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf

		OutputTo "COVERURL"
		json_select "artworkUrl100"
		Replace "100x100bb" "2000x2000bb"
		SayRest

		OutputTo "COPYRIGHT"
		json_select "copyright"
		SayRest

	EndIf
	json_select "kind"
	If "song"

		OutputTo "ITUNESARTISTID"
		json_select "artistId"
		SayNextNumber
		Say "|"

		OutputTo "ITUNESCATALOGID"
		json_select "trackId"
		SayNextNumber
		Say "|"

		OutputTo "ARTIST"
		json_select "artistName"
		SayRest
		Say "|"

		OutputTo "TRACKS"
		json_select "trackCensoredName"
		If ""
			json_select "trackName"
		EndIf
		Say "|"

		OutputTo "ITUNESADVISORY"
		json_select "trackExplicitness"
		Replace "notExplicit" "0"
		Replace "explicit" "1"
		Replace "cleaned" "2"
		SayRest
		Say "|"

		OutputTo "ITUNESMEDIATYPE"
		Say "Normal"
		Say "|"

		OutputTo "YEAR"
		json_select "releaseDate"
		SayRest		
		Say "|"

		OutputTo "TOTALDISCS"
		json_select "discCount"
		SayNextNumber
		Say "|"

		OutputTo "DISCNUMBER"
		json_select "discNumber"
		SayNextNumber
		Say "|"

		OutputTo "TOTALTRACKS"
		json_select "trackCount"
		SayNextNumber
		Say "|"

		OutputTo "TRACK"
		json_select "trackNumber"
		SayNextNumber
		Say "|"

		OutputTo "_LENGTH"
		json_select "trackTimeMillis"
		SayNextNumber
		Say "|"

		OutputTo "GENRE"
		json_select "primaryGenreName"
		If "Country"
			OutputTo "ITUNESGENREID"
			Say "6"
			Say "|"
		EndIf
		If "Electronic"
			OutputTo "ITUNESGENREID"
			Say "7"
			Say "|"
		EndIf
		If "Electronica"
			OutputTo "ITUNESGENREID"
			Say "1058"
			Say "|"
		EndIf
		If "Singer/Songwriter"
			OutputTo "ITUNESGENREID"
			Say "10"
			Say "|"
		EndIf
		If "Pop"
			OutputTo "ITUNESGENREID"
			Say "14"
			Say "|"
		EndIf
		If "R&B/Soul"
			OutputTo "ITUNESGENREID"
			Say "15"
			Say "|"
		EndIf
		If "Soundtrack"
			OutputTo "ITUNESGENREID"
			Say "16"
			Say "|"
		EndIf
		If "Dance"
			OutputTo "ITUNESGENREID"
			Say "17"
			Say "|"
		EndIf
		If "House"
			OutputTo "ITUNESGENREID"
			Say "1048"
			Say "|"
		EndIf
		If "Hip-Hop/Rap"
			OutputTo "ITUNESGENREID"
			Say "18"
			Say "|"
		EndIf
		If "Worldwide"
			OutputTo "ITUNESGENREID"
			Say "19"
			Say "|"
		EndIf
		If "Alternative"
			OutputTo "ITUNESGENREID"
			Say "20"
			Say "|"
		EndIf
		If "Rock"
			OutputTo "ITUNESGENREID"
			Say "21"
			Say "|"
		EndIf
		If "J-Pop"
			OutputTo "ITUNESGENREID"
			Say "27"
			Say "|"
		EndIf
		If "Anime"
			OutputTo "ITUNESGENREID"
			Say "29"
			Say "|"
		EndIf
		If "K-Pop"
			OutputTo "ITUNESGENREID"
			Say "51"
			Say "|"
		EndIf
		SayRest
		Say "|"

	EndIf
	json_foreach_end
EndIf
