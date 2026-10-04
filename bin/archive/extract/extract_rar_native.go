// https://github.com/Senzdetta/Ares

package main

import (
    "os"
    "io"
    "path/filepath"
    "github.com/nwaples/rardecode/v2"
)

func extractRarNative(src, dest, password string) error {
    var opts []rardecode.Option
    if password != "" {
        opts = append(
            opts,
            rardecode.Password(password),
        )
    }

    r, err := rardecode.OpenReader(src, opts...)
    if err != nil {
        return err
    }
    defer r.Close()

    for {
        hdr, err := r.Next()
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

        if hdr.IsDir {
            if err := os.MkdirAll(
                fp,
                0755,
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

        out, err := os.Create(fp)
        if err != nil {
            return err
        }

        if _, err := io.Copy(out, r); err != nil {
            out.Close()
            return err
        }
        out.Close()
    }
    return nil
}

// Copyright (c) 2026 Senzdetta