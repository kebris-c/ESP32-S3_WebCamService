#include "include/SDService.hpp"

/*	If using SD_MMC	*/
bool	SDService::init(void)
{
	uint64_t	cardSize;
	uint8_t		cardType;

	SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
	if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5))
	{
		Log::error("SD card mount failed (SD_MMC.begin())");
		return (false);
	}
	cardType = SD_MMC.cardType();
	if (cardType == CARD_NONE)
	{
		Log::error("No SD card attached");
		return (false);
	}
	cardSize = SD_MMC.cardSize() / (1024 * 1024);
	Log::info(("SD card mounted. Size: " + String(cardSize) + "MB").c_str());
	return (true);
}

bool	SDService::writeFile(const char *path, const uint8_t *data, size_t len)
{
	File	file;
	size_t	written;

	file = SD_MMC.open(path, FILE_WRITE);
	if (!file)
	{
		Log::error("Failed to open file on SD");
		return (false);
	}
	written = file.write(data, len);
	file.close();
	if (written != len)
	{
		Log::error("Incomplete write to SD");
		return (false);
	}
	Log::info(("File written: " + String(path)).c_str());
	return (true);
}