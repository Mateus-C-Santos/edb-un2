# Diretórios dos subdiretórios
SUBDIRS = q1 q2 q3

# Timestamp para o nome do arquivo zip
TIMESTAMP = $(shell date +%H%M%S%d%m%Y)

# Nome do arquivo zip
ZIPFILE = EDB1-Prof_Eiji-Prova2_v-$(TIMESTAMP).zip

# Diretório de destino padrão
DESTDIR ?= .

# Regra padrão
all:
	@for dir in $(SUBDIRS); do \
		echo "Running 'make all' in $$dir..."; \
		$(MAKE) -C $$dir all || exit 1; \
	done

# Regra clean
clean:
	rm -rf *.log
	@for dir in $(SUBDIRS); do \
		echo "Running 'make clean' in $$dir..."; \
		$(MAKE) -C $$dir clean || exit 1; \
	done

# Regra run-test
run-test: clean
	@for dir in $(SUBDIRS); do \
		echo "Running 'make test' in $$dir..."; \
		$(MAKE) -C $$dir test > $$dir.comp.log 2>&1; \
		echo "Running 'make run-test' in $$dir..."; \
		$(MAKE) -C $$dir run-test > $$dir.test.log 2>&1; \
	done

# Regra zip
zip: clean
	@echo "Creating zip archive $(ZIPFILE)..."
	@zip -r $(ZIPFILE) . -x "*.zip" -x ".DS_Store" -x "*/.DS_Store" || exit 1
	@if [ "$(DESTDIR)" != "." ]; then \
		echo "Moving $(ZIPFILE) to $(DESTDIR)..."; \
		mv $(ZIPFILE) $(DESTDIR) || exit 1; \
	fi
