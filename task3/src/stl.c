#include "stl.h"

Object3D *new_object(void)
{
    Object3D *obj = (Object3D *)malloc(sizeof(Object3D));

    obj->tris = NULL;
    obj->tri_count = 0;

    return obj;
}

void add_tri(Object3D *obj, Tri tri)
{
    obj->tris = (Tri *)realloc(obj->tris, sizeof(Tri) * (obj->tri_count + 1));

    obj->tris[obj->tri_count] = tri;

    obj->tri_count += 1;
}

Object3D *object_from_binary(char *path)
{
    FILE *fp = fopen(path, "rb");

    if (fp == NULL)
    {
        puts("Failed to open the file.");
        exit(EXIT_FAILURE);
    }

    Object3D *obj = new_object();

    fseek(fp, 80, 0);

    unsigned short tri_count;
    fread(&tri_count, sizeof(unsigned int), 1, fp);

    obj->tris = (Tri *)realloc(obj->tris, sizeof(Tri) * tri_count);

    // fread(obj->tris, sizeof(Tri), 1, fp);
    for (int i = 0; i < tri_count; i++)
    {
        Tri tri;
        fread(&tri, sizeof(Tri) - 2, 1, fp);

        add_tri(obj, tri);
    }

    fclose(fp);

    return obj;
}

Object3D *object_from_stl(char *path)
{
    FILE *fp = fopen(path, "rb");

    if (fp == NULL)
    {
        puts("Failed to open the file.");
        exit(EXIT_FAILURE);
    }

    Object3D *obj = new_object();
    size_t len;

    char *line = NULL;

    Tri tri;
    int index = 0;

    while (getline(&line, &len, fp) != EOF)
    {
        while (*line == ' ')
        {
            line++;
        }

        float x, y, z;

        if (sscanf(line, "facet normal %f %f %f\n", &x, &y, &z) == 3)
        {
            tri.n[0] = x;
            tri.n[1] = y;
            tri.n[2] = z;
        }

        if (sscanf(line, "vertex %f %f %f\n", &x, &y, &z) == 3)
        {
            switch (index)
            {
            case 0:
                tri.v1[0] = x;
                tri.v1[1] = y;
                tri.v1[2] = z;
                break;
            case 1:
                tri.v2[0] = x;
                tri.v2[1] = y;
                tri.v2[2] = z;
                break;
            case 2:
                tri.v3[0] = x;
                tri.v3[1] = y;
                tri.v3[2] = z;
                break;
            }

            index++;
        }

        if (strcmp(line, "endfacet\n") == 0)
        {
            add_tri(obj, tri);
            index = 0;
        }
    }

    return obj;
}

void object_to_binary(Object3D *obj, char *path)
{
    FILE *fp = fopen(path, "wb");

    char padding[80] = {};
    fwrite(&padding, sizeof(char), 80, fp);

    fwrite(&obj->tri_count, sizeof(unsigned int), 1, fp);
    fwrite(obj->tris, sizeof(Tri) - 2, obj->tri_count, fp);

    fclose(fp);
}

void object_to_stl(Object3D *obj, char *solidName, char *path)
{
    FILE *fp = fopen(path, "wb");

    fprintf(fp, "solid %s\n", solidName);

    for (int i = 0; i < obj->tri_count; i++)
    {
        Tri tri = obj->tris[i];
        fprintf(fp, "  facet normal %f %f %f\n", tri.n[0], tri.n[1], tri.n[2]);
        fprintf(fp, "    outer loop\n");
        fprintf(fp, "      vertex %f %f %f\n", tri.v1[0], tri.v1[1], tri.v1[2]);
        fprintf(fp, "      vertex %f %f %f\n", tri.v2[0], tri.v2[1], tri.v2[2]);
        fprintf(fp, "      vertex %f %f %f\n", tri.v3[0], tri.v3[1], tri.v3[2]);
        fprintf(fp, "    endloop\n");
        fprintf(fp, "  endfacet\n");
    }

    fprintf(fp, "endsolid %s\n", solidName);

    fclose(fp);
}

void print_tri(Tri *tri)
{
    puts("TRI");
    printf("Normal      (%f, %f, %f)\n", tri->n[0], tri->n[1], tri->n[2]);
    printf("Vertex 1    (%f, %f, %f)\n", tri->v1[0], tri->v1[1], tri->v1[2]);
    printf("Vertex 2    (%f, %f, %f)\n", tri->v2[0], tri->v2[1], tri->v2[2]);
    printf("Vertex 3    (%f, %f, %f)\n", tri->v3[0], tri->v3[1], tri->v3[2]);
    printf("Color       %d\n", tri->color);
    puts("");
}

void print_object(Object3D *obj)
{
    puts("Object3D");
    printf("Tri count: %d\n", obj->tri_count);
    puts("");

    for (int i = 0; i < obj->tri_count; i++)
    {
        print_tri(obj->tris + i);
    }
}

void free_object(Object3D *obj)
{
    free(obj->tris);
    free(obj);
}