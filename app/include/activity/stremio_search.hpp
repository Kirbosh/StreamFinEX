/*
    Stremio search screen

    Searches Cinemeta for movies and series matching a query and shows the
    results in the poster grid. Selecting a result behaves like the home grid
    (movie -> stream picker, series -> season list).
*/
#pragma once

#include <borealis.hpp>
#include "api/stremio.hpp"

class RecyclingGrid;

class StremioSearch : public brls::Box {
public:
    explicit StremioSearch(const std::string& query);

    // Stores one batch of results (movies or series) and rebuilds the grid.
    void addResults(const std::vector<stremio::Meta>& metas, bool isSeries);

private:
    void fetchInto(const std::string& url, bool isSeries);
    void rebuild();  // interleave movies + series into the grid

    std::vector<stremio::Meta> movies, series;
    int pending = 2;  // outstanding search requests (movies + series)

    RecyclingGrid* recycler = nullptr;
};
