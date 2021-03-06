
#include <stdint.h>
#include <stdio.h>

#include "tlb.h"

// Ne pas modifier cette fonction
void
tlb_init (struct tlb *tlb, FILE * log)
{
  for (unsigned int i = 0; i < TLB_NUM_ENTRIES; i++)
    {
      tlb->entries[i].page_number = -1;
      tlb->entries[i].frame_number = -1;
    }

  tlb->log = log;
  tlb->next_entry_available = 0;
}


// Ne pas modifier cette fonction
void
tlb_clean (struct tlb *tlb)
{
  if (tlb->log)
    {
      for (unsigned int i = 0; i < TLB_NUM_ENTRIES; i++)
	{
	  fprintf (tlb->log,
		   "%d: %d -> %d\n",
		   i,
		   tlb->entries[i].page_number, tlb->entries[i].frame_number);
	}
    }
}


// Sur entrée d'un numéro de page, retourne le numéro de frame
// associé. S'il n'y a pas d'entrée correspondante à la page,
// -1 est retourné.
int32_t
tlb_lookup (struct tlb *tlb, uint16_t page_number)
{
  // Complétez cette fonction.
	for(int i=0;i<TLB_NUM_ENTRIES; i++){
		if(tlb->entries[i].page_number == page_number)
			return tlb->entries[i].frame_number;
	}
	return -1;
}

// Ajoute une entré dans le tlb. Pour bien mettre en oeuvre
// cette fonction, il est nécessaire d'avoir un algorithme
// de remplacement pour bien gérer un tlb plein.
int32_t
tlb_add_entry (struct tlb *tlb, uint16_t page_number, uint16_t frame_number)
{
  // Complétez cette fonction. 
  int32_t removed_page_number = -1;
  
  removed_page_number =  tlb->entries[tlb->next_entry_available].page_number;
  
  tlb->entries[tlb->next_entry_available].page_number = page_number;
  tlb->entries[tlb->next_entry_available].frame_number = frame_number;
  
  tlb->next_entry_available = (tlb->next_entry_available + 1) % TLB_NUM_ENTRIES;
  return removed_page_number;
}
