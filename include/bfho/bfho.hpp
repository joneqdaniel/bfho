#pragma once

namespace bfho
{

struct model : std::vector<u8>
{
	struct entry
	{
		char*   data = nullptr;
		size_t  size = 0;
		ssize_t read = PATH_MAX;
		entry() : data(nullptr), size(0), read(PATH_MAX) {}
		bool get(FILE* src) { return (read = getline(&data, &size, src)) != -1; }
	};

	u32                   checksum;
	std::filesystem::path filename;
	std::string               name;
	obj*                       obj;

	model(FILE* file)
	{
		std::pair<entry,entry> src;
		if(src.first.get(file) && src.second.get(file))
		{
			char tmp[PATH_MAX] = { '\0' };

			/* parse line entry */
			sscanf(src.first.data, "%08x  %s\n", &checksum, tmp);
			if(tmp[strlen(tmp) - 1] == '\n') tmp[strlen(tmp) - 1] = '\0';
			filename = std::filesystem::path(tmp);

			/* parse name entry */
			sscanf(src.second.data, "; %s\n", tmp);
			if(tmp[strlen(tmp) - 1] == '\n') tmp[strlen(tmp) - 1] = '\0';
			name = std::string(&tmp[2]);

			/* read line entry data */ 
			size_t size = 0;
			if(std::exists(filename) && (size = std::file_size(filename)))
			{
				this->resize(size);
				FILE* fp = fopen(filename.c_str(), "r");
				if(fp != NULL && (size = fread(this->data(), sizeof(u8), size, fp)) == this->size() && fclose(fp) == 0 && (checksum = crc32(CRC_CRC32, CRC_START_32, this->data(), this->size())) == checksum)
				{
					sprintf(&tmp, "MODEL LOADED %s %08X/%08X %s", model->filename, model->checksum, checksum, model->name);
					model->obj = obj_create(model->filename);
					bf::log.queue(tmp);
					if(obj(filename)) return;
				}
			}
			
		}
		asprintf(&tmp, "MODEL LOAD FAILED %s %08X/%08X %s", model->filename, model->checksum, checksum, name);
		bf::log.queue(tmp);
		this->clear();
	}
	static constexpr bool skip(FILE* fp)
	{
	}
	struct table : std::vector(model)
	{
		table(std::filesystem::path models)
		{
			size_t cnt = 0;
			FILE* fp = NULL;
			models = DATA_DIR / models;
			char* cwd = get_current_dir();

			if(!std::exists(models)) return;
			size_t len = std::file_size(models);
			if(len == 0) return;

			/* open models.cfg */
			if((fp = fopen(models.c_str(), "r")) == NULL) return;

			/* skip first entry which is a texture */
			if(!model::skip(fp)) { fclose(fp); return; }

			/* count models */
			while(model::skip(file)) cnt++; rewind(fp); if(!model::skip(fp)) { fclose(fp); return; }

			/* allocate models */
			this->resize(cnt);

			/* read models at DATA_DIR */
			chdir(DATA_DIR);
			size_t skipped = 0;
			for(size_t i = 0; i < this->size(); i++)
			{
				(*this)[i - skipped] = model(fp);
				if((*this)[i - skipped].size() == 0)
					skipped++;
			}
			/* print loaded model info */
			fsprintf(stdout, "[RES][CFG][%s][%zu/%zu]\t[%c]", models.c_str(), this->size() - skipped, this->size(), (this->size() - skipped) > 0 ? "X" : "");
			fclose(fp);
			dst.resize(this->size() - skipped);
			chdir(cwd);
		}
	};
};

};
