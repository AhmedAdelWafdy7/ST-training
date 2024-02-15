#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

struct partition_entry {
    uint8_t boot_indicator;
    uint8_t start_head;
    uint8_t start_sector;
    uint8_t start_cylinder;
    uint8_t partition_type;
    uint8_t end_head;
    uint8_t end_sector;
    uint8_t end_cylinder;
    uint32_t start_sector_lba;
    uint32_t total_sectors;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <disk_device>\n", argv[0]);
        return 1;
    }

    char *disk_device = argv[1];
    int fd = open(disk_device, O_RDONLY);
    if (fd == -1) {
        perror("Error opening disk device");
        return 1;
    }

    // Seek MBR
    if (lseek(fd, 0x1BE, SEEK_SET) == -1) {
        perror("Error seeking to MBR");
        close(fd);
        return 1;
    }

    // Read partition table entries
    struct partition_entry entry;
    for (int i = 0; i < 4; i++) {
        if (read(fd, &entry, sizeof(struct partition_entry)) != sizeof(struct partition_entry)) {
            perror("Error reading partition entry");
            close(fd);
            return 1;
        }

        
        if (entry.partition_type == 0x05 || entry.partition_type == 0x0F) {
            printf("Partition %d (Extended):\n", i + 1);
            
        } else {
            printf("Partition %d:\n", i + 1);
            printf("Partition type: 0x%02X\n", entry.partition_type);
            printf("Start sector: %u\n", entry.start_sector_lba);
            printf("Total sectors: %u\n", entry.total_sectors);
            printf("\n");
        }
    }

    close(fd);
    return 0;
}

