set(LABLIST
  LAB1
  LAB2
  test
  )

foreach(LAB ${LABLIST})
  add_subdirectory(${LAB})
endforeach(LAB ${LABLIST})

set(LABLIST ${LABLIST} PARENT_SCOPE)
