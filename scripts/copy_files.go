package main

import (
	"io"
	"log"
	"os"
)

type file_data struct {
	file_source_path string
	file_source_name string
	file_dest_path   string
	file_dest_name   string
}

var build_dir string = "./out/build/x64-Debug/anthill-game-engine/"

func main() {
	log.Println("Start copy_files.go ...")
	configs := [...]file_data{
		{"./resource/", "windows_core.cfg.json", build_dir, "windows_core.cfg.json"},
		{"./resource/", "window_system.cfg.json", build_dir, "window_system.cfg.json"},
		{"./third-party-libs/SDL2-2.0.14/lib/x64/", "SDL2.dll", build_dir, "SDL2.dll"},
	}

	for _, cfg := range configs {
		log.Println("file_source_path = " + cfg.file_source_path)
		log.Println("file_dest_name = " + cfg.file_dest_name)
		log.Println("file_dest_path = " + cfg.file_dest_path)
		log.Println("file_dest_name = " + cfg.file_dest_name)

		err := os.MkdirAll(cfg.file_dest_path, 0777)
		if err != nil {
			log.Fatal(err)
		}

		sFile, err := os.Open(cfg.file_source_path + cfg.file_source_name)
		if err != nil {
			log.Fatal(err)
		}

		defer sFile.Close()

		dFile, err := os.Create(cfg.file_dest_path + cfg.file_dest_name)
		if err != nil {
			log.Fatal(err)
		}
		defer dFile.Close()

		_, err = io.Copy(dFile, sFile)
		if err != nil {
			log.Fatal(err)
		}

		err = dFile.Sync()
		if err != nil {
			log.Fatal(err)
		}
	}
}
