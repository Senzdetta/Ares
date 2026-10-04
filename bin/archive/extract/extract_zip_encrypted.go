// https://github.com/Senzdetta/Ares

package main

import (
    "fmt"
    "io"
    "os"
    "path/filepath"
    yekazip "github.com/yeka/zip"
)

func extractZipEncrypted(src, dest, password string) error {
    r, err := yekazip.OpenReader(src)
    if err != nil {
        return err
    }
    defer r.Close()

    for _, f := range r.File {
        fp, err := safeJoin(dest, f.Name)
        if err != nil {
            return err
        }

        if f.FileInfo().IsDir() {
            if err := os.MkdirAll(
                fp, f.Mode(),
            ); err != nil {
                return err
            }
            continue
        }

        if err := os.MkdirAll(
            filepath.Dir(fp),
            0755,
        ); err != nil {
            return err
        }

        if f.IsEncrypted() {
            f.SetPassword(password)
        }

        rc, err := f.Open()
        if err != nil {
            return fmt.Errorf(
                "failed to open %s (wrong password?): %w",
                f.Name, err,
            )
        }

        out, err := os.OpenFile(
            fp,
            os.O_WRONLY|os.O_CREATE|os.O_TRUNC,
            f.Mode(),
        )

        if err != nil {
            rc.Close()
            return err
        }

        _, err = io.Copy(out, rc)
        out.Close()
        rc.Close()
        if err != nil {
            return err
        }
    }
    return nil
}

// Copyright (c) 2026 Senzdetta