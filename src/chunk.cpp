#include "../include/chunk.h"

namespace Rw
{
void Chunk::AddChild(Chunk *chunk)
{
    if (this->child)
    {
        Chunk *last = this->child;

        while (last->next)
        {
            last = last->next;
        }

        last->next = chunk;
    }
    else
    {
        this->child = chunk;
    }
}

void Chunk::RemoveChild(Chunk *chunk)
{
    Chunk *cur = this->child;
    Chunk *prev = NULL;

    while (cur && cur != chunk)
    {
        prev = cur;
        cur = cur->next;
    }

    if (cur)
    {
        if (prev)
        {
            prev->next = cur->next;
        }
        else
        {
            this->child = cur->next;
        }
    }
}

Chunk *Chunk::GetChild(UInt32 index) const
{
    Chunk *child = this->child;

    while (child && index > 0)
    {
        child = child->next;
        index--;
    }

    return child;
}

Chunk *Chunk::GetChildByType(UInt32 type, UInt32 index) const
{
    Chunk *child = this->child;

    while (child)
    {
        if (child->type == type)
        {
            if (index == 0)
            {
                break;
            }

            index--;
        }

        child = child->next;
    }

    return child;
}

UInt32 Chunk::ChildCount() const
{
    Chunk *child = this->child;
    UInt32 count = 0;

    while (child)
    {
        count++;
        child = child->next;
    }

    return count;
}

UInt32 Chunk::ChildCountByType(UInt32 type) const
{
    Chunk *child = this->child;
    UInt32 count = 0;

    while (child)
    {
        if (child->type == type)
        {
            count++;
        }

        child = child->next;
    }

    return count;
}

void Chunk::SetParent(Chunk *newParent)
{
    if (this->parent)
    {
        this->parent->RemoveChild(this);
    }

    newParent->AddChild(this);
}

void Chunk::SetVersionRecursive(UInt32 version)
{
    this->version = version;

    Chunk *child = this->child;

    while (child)
    {
        child->SetVersionRecursive(version);
        child = child->next;
    }
}

void Chunk::SetBuildNumRecursive(UInt32 buildNum)
{
    this->buildNum = buildNum;

    Chunk *child = this->child;

    while (child)
    {
        child->SetBuildNumRecursive(buildNum);
        child = child->next;
    }
}
}