// https://github.com/Zeronetsec/Ares

package main

import (
    "io"
    "os"
    "path/filepath"
    "archive/tar"
)

func extractTarStream(r io.Reader, dest string) error {
    tr := tar.NewReader(r)
    for {
        hdr, err := tr.Next()
        if err == io.EOF {
            break
        }

        if err != nil {
            return err
        }

        fp, err := safeJoin(dest, hdr.Name)
        if err != nil {
            return err
        }

        switch hdr.Typeflag {
            case tar.TypeDir:
                if err := os.MkdirAll(
                    fp,
                    os.FileMode(hdr.Mode),
                ); err != nil {
                    return err
                }
            case tar.TypeReg:
                if err := os.MkdirAll(
                    filepath.Dir(fp),
                    0755,
                ); err != nil {
                    return err
                }

                out, err := os.OpenFile(
                    fp,
                    os.O_WRONLY|os.O_CREATE|os.O_TRUNC,
                    os.FileMode(hdr.Mode),
                )

                if err != nil {
                    return err
                }

                if _, err := io.Copy(out, tr); err != nil {
                    out.Close()
                    return err
                }

                out.Close()
        }
    }
    return nil
}

// Copyright (c) 2026 Zeronetsec