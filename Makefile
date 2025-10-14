@all: ./builddir/rubik

./builddir/rubik: ./builddir
	ninja -C ./builddir

./builddir: meson.build
	meson setup builddir --reconfigure

clean:
	rm -rf builddir

install: ./builddir/rubik
	install -d $(DESTDIR)/usr/bin
	install ./builddir/rubik $(DESTDIR)/usr/bin/rubik

run: ./builddir/rubik
	./builddir/rubik
