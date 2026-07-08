<p align="center">
  <img src="images/logo.png" alt="StreamFinEX" width="160" />
</p>

<h1 align="center">StreamFinEX</h1>

A **streaming-only Stremio client for homebrewed Nintendo Switch**. This is a fork of
[StreamFin](https://github.com/scamNscoot/StreamFin) (itself built on
[Switchfin](https://github.com/dragonflylee/switchfin), with the Jellyfin data layer replaced by
the [Stremio addon protocol](https://github.com/Stremio/stremio-addon-sdk/blob/master/docs/protocol.md)),
focused on making the experience look and feel like **actual Stremio**.

Browse Cinemeta catalogs, search, open a title page with cast & plot, pick a stream, and play —
all natively on the Switch with MPV. No content is included: **you bring your own Stremio stream
addon URL**, which the app asks for on first launch.

## Download

Grab the latest `StreamFin.nro` from the
[**Releases page**](https://github.com/Kirbosh/StreamFinEX/releases) and copy it to `/switch/`
on your SD card. Every push to this repo builds a fresh release automatically.

## Screenshots

| Home (ocean theme) | Title details |
|---|---|
| ![Home screen](images/capture-home.jpg) | ![Title details](images/capture-detail.jpg) |

| Episodes | Playback |
|---|---|
| ![Episode list](images/capture-episodes.jpg) | ![Player](images/capture-play.jpg) |

## Features

- **Stremio-style look** — dark ocean-navy gradient theme with purple accents, official Stremio
  icon, and a glowing focus outline that breathes between ocean blue and purple
- **32 home rows** — Popular / New / Top Rated / genre rows for movies & series (Cinemeta),
  a **Surprise Me** row with random picks each launch, and **Anime** via the Kitsu addon,
  with **IMDb rating badges** on every poster
- **Smart navigation** — moving between rows lands on the poster directly above/below you;
  rows scroll poster-by-poster with a sliver of the next/previous poster at each edge
- **Library** — save any title with X (dot badge); the home row shows your newest saves plus a
  See-all card opening a full grid with **search and sort** (recent / name / year / rating)
- **Continue Watching** — resumes where you left off; exiting playback drops you right back on it
- **Title details** — poster, year, runtime, IMDb rating, genres, description, cast, director
- **Series support** — seasons → episodes with air dates → stream picker
- **Search** — press Y anywhere on home, or use the search button in the top bar
- **Custom player controls** tuned for streaming (seek on shoulders, lock screen, stream info)
- Streams play as direct HTTPS URLs through MPV — nothing torrent-related runs on the Switch

## Setup

1. Copy `StreamFin.nro` to `/switch/` on your SD card.
2. **Recommended:** while the SD card is still in your PC, create a plain-text file at
   `/switch/streamfin-addon.txt` containing your **stream addon URL** — the base URL of any
   Stremio addon that implements the `stream` resource (with or without `/manifest.json`).
   StreamFinEX imports it automatically at launch — no typing on the console. Editing the file
   later updates the settings too. Full format (all lines optional, `#` for comments):

   ```
   https://your-stream-addon.example.com/...
   rpdb=YOUR_RPDB_KEY
   subtitles=https://your-subtitles-addon.example.com/...
   ```
3. Alternatively, launch without the file and type the URL into the on-screen keyboard when
   prompted (works, but long addon URLs are painful to type).
4. Change it any time by pressing **−** on the home screen, or by editing the text file. The
   active URL is stored at `sdmc:/config/StreamFin/stremio_addon.json`.

Catalog browsing works without an addon; you only need one to actually play streams.

### Poster ratings (optional)

Out of the box, every poster shows a small **★ IMDb badge** using data already present in the
Cinemeta catalogs — no key needed. If you prefer posters with the rating **baked into the
artwork**, add a poster provider to `streamfin-addon.txt`:

- `rpdb=YOUR_KEY` — [RatingPosterDB](https://ratingposterdb.com) rated posters (free personal
  key available; paid tiers add more rating sources).
- `poster=https://.../{imdbId}/...` — any provider that serves poster images by IMDb id;
  `{imdbId}` is replaced with the title's id (e.g. `tt1375666`).

When a poster provider is set, the text badge is hidden automatically (the rating is in the
image). Remove the line to switch back.

### Subtitles addon (optional)

Embedded subtitle tracks always work out of the box. To also pull subtitles from a Stremio
**subtitles addon** (SubSource, OpenSubtitles, …), add its base URL to `streamfin-addon.txt`:

```
subtitles=https://your-subtitles-addon.example.com/...
```

When playback starts, StreamFinEX fetches subtitles for that exact title/episode and adds them to
the player — pick one under **+ → Subtitle** (one per language, alongside any embedded tracks).

## Controls

| Context | Button | Action |
|---|---|---|
| Home | Y | Search (also: top-bar search button) |
| Home | X | Add/remove from Library |
| Home | − | Set stream addon URL |
| Library | Y | Search within the library |
| Detail page | A on ▶ | Watch (movies) / Episodes (series) |
| Detail page | X | Add/remove from Library |
| Player | L / R | Seek back / forward |
| Player | X | Lock screen |
| Player | − | Stream info |
| Player | + | Settings |

## Building from source

Prebuilt releases are made by [GitHub Actions](.github/workflows/build-switch.yaml). To build
locally you need [devkitPro](https://devkitpro.org/) with devkitA64/libnx and Switchfin's custom
[switch-portlibs](https://github.com/dragonflylee/switchfin/releases/tag/switch-portlibs)
(mbedtls, libssh2, dav1d, curl, ffmpeg, libmpv, libjpeg-turbo).

```bash
export PKG_CONFIG_LIBDIR=/opt/devkitpro/portlibs/switch/lib/pkgconfig
export PKG_CONFIG_PATH=/opt/devkitpro/portlibs/switch/lib/pkgconfig
cmake -B build_switch -G Ninja -DPLATFORM_SWITCH=ON -DBUILTIN_NSP=OFF
ninja -C build_switch StreamFin.nro
```

## Credits

- [StreamFin](https://github.com/scamNscoot/StreamFin) by scamNscoot — the Stremio-on-Switch
  base this repository forks
- [Switchfin](https://github.com/dragonflylee/switchfin) by dragonflylee — the original app
  (player, UI framework integration, build system)
- [borealis](https://github.com/natinusala/borealis) — Switch-style UI library
- [Stremio](https://www.stremio.com/) — the addon protocol, the public Cinemeta catalog, and the
  logo used for the app icon

## Contact

Bugs and feature requests: please [open an issue](https://github.com/Kirbosh/StreamFinEX/issues).

## Disclaimer

This app is a generic client for the open Stremio addon protocol. It ships with no media and no
addon. What you stream is determined entirely by the addon URL you configure — you are responsible
for using addons and content you have the right to access.

## License

[Apache-2.0](LICENSE), same as Switchfin.
