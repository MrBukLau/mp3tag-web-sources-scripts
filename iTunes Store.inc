# iTunes API parser for MP3Tag v3
[Name]=iTunes
[BasedOn]=https://itunes.apple.com/
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

		OutputTo "ALBUMARTISTID"
		json_select "artistId"
		SayNextNumber

		OutputTo "plID"
		json_select "collectionId"
		SayNextNumber

		OutputTo "AMGARTISTID"
		json_select "amgArtistId"
		SayNextNumber

		OutputTo "ALBUMARTIST"
		json_select "artistName"
		Replace "Various Artists" ""
		Replace "Varios Artistas" ""
		Replace "Vários Artistas" ""
		Replace "群星" ""
		Replace "Eri Esittäjiä" ""
		Replace "Multi-interprètes" ""
		Replace "Verschiedene Interpreten" ""
		Replace "Artisti Vari" ""
		Replace "ヴァリアス・アーティスト" ""
		Replace "Diverse Artister" ""
		Replace "Разные артисты" ""
		Replace "Blandade Artister" ""
		Replace "Çeşitli Sanatçılar" ""
		Replace "مختلف الفنانين" ""
		Replace "فنانون متنوعون" ""
		Replace "فنانون متعددون" ""
		Replace "Різні виконавці" ""
		Replace "Nhiều Nghệ Sĩ" ""
		If ""
			OutputTo "COMPILATION"
			Say "1"
			OutputTo "ALBUMARTIST"
			Say ""
		Else
			SayRest
		EndIf

		OutputTo "ALBUM"
		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		Replace "[" "("
		Replace "]" ")"
		SayUntil "(Remastered)"
		IfNot ""
			OutputTo "REMASTEREDALBUM"
			Say "1"
		EndIf

		OutputTo "COVERURL"
		json_select "artworkUrl100"
		Replace "100x100bb" "10000x10000bb"
		SayRest

		OutputTo "ALBUMADVISORY"
		json_select "collectionExplicitness"
		Replace "cleaned" "2"
		Replace "explicit" "1"
		Replace "notExplicit" "0"
		SayRest
		Say "|"

		OutputTo "CONTENTADVISORY"
		json_select "contentAdvisoryRating"
		SayRest
		Say "|"

		OutputTo "ALBUMTRACKS"
		json_select "trackCount"
		SayNextNumber

		OutputTo "COPYRIGHT"
		json_select "copyright"
		SayRest

		OutputTo "YEAR"
		json_select "releaseDate"
		SayRest

		OutputTo "ALBUMGENRE"
		json_select "primaryGenreName"
		SayRest

	EndIf
	json_select "kind"
	If "song"

		OutputTo "atID"
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

		OutputTo "COLLECTIONNAME"
		json_select "collectionName"
		If ""
			json_select "collectionCensoredName"
		EndIf
		SayRest
		Say "|"

		OutputTo "TRACKS"
		json_select "trackCensoredName"
		If ""
			json_select "trackName"
		EndIf
		Replace "[" "("
		Replace "]" ")"
		SayUntil "(Remastered)"
		Say "|"
		OutputTo "REMASTERED"
		IfNot ""
			Say "1"
		EndIf
		Say "|"

		OutputTo "ITUNESADVISORY"
		json_select "trackExplicitness"
		Replace "cleaned" "2"
		Replace "explicit" "1"
		Replace "notExplicit" "0"
		SayRest
		Say "|"

		OutputTo "ITUNESMEDIATYPE"
		Say "Normal"
		Say "|"

		OutputTo "TRACKYEAR"
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
		SayRest
		Say "|"

		OutputTo "WORK"
		json_select "trackName"
		SayUntil ": "
		Say "|"

		OutputTo "MOVEMENTNAME"
		json_select "trackName"
		FindInLine ": " 1 1
		SayRest
		Say "|"

	EndIf
	json_foreach_end
EndIf
