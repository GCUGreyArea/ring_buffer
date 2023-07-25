#include <gtest/gtest.h>


#define RING_BUFFER_SIZE (6^2)
#include <libProducerConsumer.h>

TEST(ring_buffer,test_that_ring_allocation_works) {
    ring_buffer_t rb;

    ring_buffer_err_t er = rb_init(&rb,RING_BUFFER_SIZE);

    ASSERT_EQ(er,RB_ERR_OK);
    ASSERT_EQ(6^2,rb.size);

    rb_teardown(&rb);
}


TEST(ring_buffer,test_ring_buffer_can_add) {
    ring_buffer_t rb;

    ring_buffer_err_t er = rb_init(&rb,RING_BUFFER_SIZE);

    ASSERT_EQ(er,RB_ERR_OK);

    rb_add(&rb,1);
    rb_add(&rb,2);
    rb_add(&rb,3);
    rb_add(&rb,4);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_FULL,er);

    ASSERT_EQ(1,rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK,er);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK,er);
    ASSERT_EQ(2,rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK,er);
    ASSERT_EQ(3,rb_get(&rb));

    // Read past the ast element
    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_NO_DATA,er);

    ASSERT_EQ(0,rb_get(&rb));
    ASSERT_EQ(0,rb_get(&rb));
    ASSERT_EQ(0,rb_get(&rb));

    rb_add(&rb,1);
    rb_add(&rb,2);
    rb_add(&rb,3);
    rb_add(&rb,4);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_FULL,er);

    ASSERT_EQ(1,rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK,er);

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK,er);
    ASSERT_EQ(2,rb_get(&rb));

    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_OK,er);
    ASSERT_EQ(3,rb_get(&rb));

    // Read past the ast element
    er = rb_test(&rb);
    ASSERT_EQ(RB_ERR_NO_DATA,er);

    ASSERT_EQ(0,rb_get(&rb));
    ASSERT_EQ(0,rb_get(&rb));
    ASSERT_EQ(0,rb_get(&rb));

    rb_teardown(&rb);    
}

TEST(ring_buffer,test_big_ring_buffer) {

    ring_buffer_t rb;
    size_t size = 134217728; // 2^27

    ring_buffer_err_t er = rb_init(&rb,size);

    ASSERT_EQ(er,RB_ERR_OK);

    rb_teardown(&rb);    
}