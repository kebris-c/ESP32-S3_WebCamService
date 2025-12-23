#ifndef SDSERVICE_HPP
# define SDSERVICE_HPP

# include <SD_MMC.h>
# include "include/Log.hpp"

# define SD_MMC_CMD  38
# define SD_MMC_CLK  39
# define SD_MMC_D0   40

class	SDService
{
public:
	bool	init(void);
	bool	writeFile(const char *path, const uint8_t *data, size_t len);
};

#endif